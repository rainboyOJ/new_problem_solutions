/**
 * agy-tab —— 把 agy（Antigravity CLI）的无头调用放进一个 herdr tab 里跑，
 * 这样 pi 拿得到结论，用户也看得见 agy 一步步在干什么。
 *
 * 与 .agents/skills/agy-delegate/scripts/agy-ask.sh 的分工：
 *   - 那个脚本是纯终端用法（CI、批量、没有 herdr 的场景）；
 *   - 这个 extension 是交互用法：agy 的 NDJSON 事件流实时打进 tab，
 *     结束后由 pi 从事件流里取结果，成功即关 tab，失败保留 tab 供回看。
 *
 * 设计要点（对齐本机 pi-herdr-agents 的做法）：
 *   1. tab create 拿 root pane id -> pane run 投递命令，命令自己写退出 sidecar；
 *   2. 完成判定以 sidecar 文件为准（不依赖终端输出的解析）；
 *   3. tab 里显示的是经 render.py 美化过的 agy 事件流，原文另存 events.ndjson。
 */

import { execFileSync } from "node:child_process";
import { existsSync, mkdtempSync, readFileSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { join } from "node:path";

import type { ExtensionAPI, ExtensionContext } from "@earendil-works/pi-coding-agent";
import { Type } from "typebox";

const AgyTabParams = Type.Object({
	prompt: Type.String({ description: "要交给 agy 的完整提示词。只读任务请自己在提示词里写明不要改文件。" }),
	model: Type.Optional(
		Type.String({ description: "agy 模型 id，见 `agy models`，例如 gemini-3.8-flash-high、claude-opus-4-6-thinking" }),
	),
	effort: Type.Optional(
		Type.String({ description: "推理强度 low|medium|high|xhigh|max；只对部分模型有效，给 Claude 系传会直接报错" }),
	),
	write: Type.Optional(
		Type.Boolean({ description: "true 时加 --dangerously-skip-permissions，agy 才能跑命令/改文件。默认只读。" }),
	),
	cwd: Type.Optional(Type.String({ description: "agy 的工作目录，默认用 pi 当前目录" })),
	label: Type.Optional(Type.String({ description: "tab 标签，默认 agy:<提示词摘要>" })),
	background: Type.Optional(
		Type.Boolean({
			description: "true 时立刻返回 pane id，等 agy 跑完再以一条消息唤醒 pi；适合并发派多个 agy。默认 false（阻塞等结果）。",
		}),
	),
	timeoutSec: Type.Optional(Type.Number({ description: "等待上限秒数，默认 300" })),
});

interface AgyRunDetails {
	paneId?: string;
	conversationId?: string;
	status?: string;
	denied?: string[];
	durationSec?: number;
	totalTokens?: number;
	tabKept?: boolean;
	logDir?: string;
	error?: string;
	background?: boolean;
}

/**
 * 该 tab 里跑的脚本。写成独立文件而不是一行命令，是因为 `pane run` 把文本直接打进
 * 交互式 shell 的行编辑器，多行命令会停在续行提示符上卡住。
 */
const RUN_SH = String.raw`#!/usr/bin/env bash
set -o pipefail
BASE="$1"; shift
agy "$@" < "$BASE/prompt.ndjson" \
  | tee "$BASE/events.ndjson" \
  | python3 "$BASE/render.py"
rc=$?
python3 - "$BASE" "$rc" <<'PY'
import json, os, sys, time
base, rc = sys.argv[1], int(sys.argv[2])
tmp = os.path.join(base, "done.json.tmp")
with open(tmp, "w", encoding="utf-8") as f:
    json.dump({"rc": rc, "finished_at": time.time()}, f)
os.replace(tmp, os.path.join(base, "done.json"))
PY
# 结尾哨兵用 printf 拼出来，命令文本里不含完整字样，避免 pane 输出匹配误判
printf '__AGY_%s_%s__\n' DONE "$rc"
`;

/** 把 agy 的 NDJSON 事件渲染成人能看的一行一件事。 */
const RENDER_PY = String.raw`
import json, sys

def cut(text, n=90):
    text = " ".join(str(text).split())
    return text if len(text) <= n else text[: n - 1] + "…"

for line in sys.stdin:
    line = line.strip()
    if not line.startswith("{"):
        if line:
            print("  " + cut(line), flush=True)
        continue
    try:
        event = json.loads(line)
    except json.JSONDecodeError:
        continue
    kind = event.get("event")
    if kind == "init":
        init = event.get("init", {})
        tools = len(init.get("tools") or [])
        print(f"▶ agy 会话启动 · cwd={init.get('cwd')} · 工具 {tools} 个", flush=True)
    elif kind == "step_update":
        step = event.get("step_update", {})
        state = step.get("state")
        stype = step.get("step_type")
        if stype == "tool" and state == "ACTIVE":
            params = (step.get("tool_info") or {}).get("parameters") or {}
            detail = params.get("CommandLine") or params.get("AbsolutePath") or params.get("TargetFile") or params
            print(f"  ⚙ {step.get('tool_name')}  {cut(detail)}", flush=True)
        elif stype == "agent_response" and step.get("text_delta"):
            print(f"  ✎ {cut(step['text_delta'])}", flush=True)
    elif kind == "result":
        result = event.get("result", {})
        usage = result.get("usage") or {}
        mark = "✔" if result.get("status") == "SUCCESS" else "✘"
        print(f"{mark} {result.get('status')} · {result.get('duration_seconds', 0):.1f}s · "
              f"tokens {usage.get('total_tokens')}", flush=True)
        if result.get("denied_actions"):
            names = ", ".join(d.get("display_name") or d.get("action", "?") for d in result["denied_actions"])
            print(f"  ! 被权限拒绝: {names} (只读模式下 agy 不能跑命令)", flush=True)
`;

function herdr(args: string[], timeout = 20000): string {
	return execFileSync("herdr", args, { encoding: "utf8", timeout, killSignal: "SIGKILL", stdio: "pipe" });
}

function parseHerdrJson(raw: string): any {
	const start = raw.indexOf("{");
	if (start < 0) return null;
	try {
		return JSON.parse(raw.slice(start));
	} catch {
		return null;
	}
}

function slug(text: string): string {
	const flat = text.replace(/\s+/g, " ").trim();
	return flat.length > 22 ? flat.slice(0, 22) + "…" : flat || "task";
}

function shellQuote(value: string): string {
	return `'${value.replace(/'/g, `'\\''`)}'`;
}

function sleep(ms: number): Promise<void> {
	return new Promise((resolve) => setTimeout(resolve, ms));
}

/** 从事件流里取最后一条 result 事件。 */
function readResult(eventsPath: string): any {
	if (!existsSync(eventsPath)) return null;
	let found: any = null;
	for (const line of readFileSync(eventsPath, "utf8").split("\n")) {
		const trimmed = line.trim();
		if (!trimmed.startsWith("{")) continue;
		try {
			const parsed = JSON.parse(trimmed);
			if (parsed?.event === "result") found = parsed.result;
		} catch {
			// 半行或非 JSON 事件，忽略
		}
	}
	return found;
}

interface PendingRun {
	base: string;
	paneId: string;
	label: string;
	deadline: number;
}

/** 后台模式登记表：paneId -> 运行信息。poller 每秒查一次 sidecar。 */
const pending = new Map<string, PendingRun>();
let poller: ReturnType<typeof setInterval> | null = null;

function detailOf(result: any, denied: string[]): string {
	return [
		result?.status ? `status ${result.status}` : null,
		result?.conversation_id ? `cid ${result.conversation_id}` : null,
		result?.duration_seconds ? `${result.duration_seconds.toFixed(1)}s` : null,
		denied.length ? `被拒工具 ${denied.join(",")}` : null,
	]
		.filter(Boolean)
		.join(" · ");
}

/** 收尾：成功关 tab 清日志，失败留现场，然后用一条 steer 消息唤醒 pi。 */
function finishRun(api: ExtensionAPI, run: PendingRun, timedOut: boolean): void {
	const eventsPath = join(run.base, "events.ndjson");
	const result = readResult(eventsPath);
	const response = (result?.response ?? "").trim();
	const denied: string[] = (result?.denied_actions ?? []).map((d: any) => d?.display_name || d?.action || "?");
	const ok = !timedOut && result?.status === "SUCCESS" && response.length > 0 && denied.length === 0;
	const meta = detailOf(result, denied);

	if (ok) {
		try {
			herdr(["pane", "close", run.paneId]);
		} catch {
			// 关不掉不算失败
		}
		rmSync(run.base, { recursive: true, force: true });
	} else {
		try {
			herdr(["pane", "rename", run.paneId, `${run.label} ✗`]);
		} catch {
			// 改名只是提示
		}
	}

	const head = ok
		? `agy 后台任务完成 (tab ${run.paneId} 已关闭)`
		: timedOut
			? `agy 后台任务超时 (tab ${run.paneId} 保留现场)`
			: `agy 后台任务未成功 (tab ${run.paneId} 保留现场)`;
	const body = ok
		? `${head}\n${meta}\n\n${response.slice(0, 6000)}${response.length > 6000 ? `\n…(已截断，原文在 ${eventsPath})` : ""}\n\n[这是外部模型 agy 的结论，落盘前请自己复核。]`
		: `${head}\n${meta}\n${denied.length ? "它想用被禁止的工具；要它自己动手就重新调用并传 write=true。\n" : ""}事件原文: ${eventsPath}\n看现场: herdr pane read ${run.paneId}`;

	api.sendMessage(
		{
			customType: "agy_tab_result",
			content: body,
			display: true,
			details: {
				paneId: run.paneId,
				conversationId: result?.conversation_id,
				status: result?.status,
				denied,
				durationSec: result?.duration_seconds,
				totalTokens: result?.usage?.total_tokens,
				tabKept: !ok,
				logDir: run.base,
				background: true,
				error: ok ? undefined : timedOut ? "timeout" : "not-success",
			} as AgyRunDetails,
		},
		{ triggerTurn: true, deliverAs: "steer" },
	);
}

/** 懒启动 poller：没有后台任务时不占定时器。 */
function ensurePoller(api: ExtensionAPI): void {
	if (poller) return;
	poller = setInterval(() => {
		if (pending.size === 0) {
			if (poller) clearInterval(poller);
			poller = null;
			return;
		}
		for (const run of [...pending.values()]) {
			const done = existsSync(join(run.base, "done.json"));
			const timedOut = !done && Date.now() > run.deadline;
			if (!done && !timedOut) continue;
			pending.delete(run.paneId);
			try {
				finishRun(api, run, timedOut);
			} catch {
				// 单个任务的通知失败不影响其余后台任务
			}
		}
	}, 1000);
}

export default function (pi: ExtensionAPI) {
	pi.on("session_shutdown", () => {
		if (poller) clearInterval(poller);
		poller = null;
		pending.clear();
	});

	pi.registerTool({
		name: "agy_tab",
		label: "agy (herdr tab)",
		description:
			"在 herdr 的独立 tab 里跑一次 agy（Antigravity CLI）无头调用，用户能实时看到 agy 的工具调用与推理片段；" +
			"结束后把 agy 的结论返回。默认只读（agy 不能跑命令/改文件）；需要它自己动手时传 write=true。" +
			"适合跨模型的独立评审、证明挑错、多视角思考。agy 的结论必须自己复核，不要直接采信。",
		parameters: AgyTabParams,

		async execute(_toolCallId, params, signal, onUpdate, ctx: ExtensionContext) {
			const cwd = params.cwd || ctx.cwd;
			const timeoutSec = params.timeoutSec && params.timeoutSec > 0 ? params.timeoutSec : 300;
			const label = params.label || `agy: ${slug(params.prompt)}`;

			const base = mkdtempSync(join(tmpdir(), "agy-tab-"));
			const promptPath = join(base, "prompt.ndjson");
			const eventsPath = join(base, "events.ndjson");
			const sidecarPath = join(base, "done.json");
			writeFileSync(promptPath, JSON.stringify({ event: "user", message: { content: params.prompt } }) + "\n", "utf8");
			writeFileSync(join(base, "render.py"), RENDER_PY, "utf8");
			const runSh = join(base, "run.sh");
			writeFileSync(runSh, RUN_SH, { encoding: "utf8", mode: 0o755 });

			const agyArgs = ["--input-format", "stream-json", "--output-format", "stream-json"];
			if (params.model) agyArgs.push("--model", params.model);
			if (params.effort) agyArgs.push("--effort", params.effort);
			if (params.write) agyArgs.push("--dangerously-skip-permissions");

			// 非 herdr 环境：退化成普通子进程，没有 tab 可看，但结论一样拿得到。
			if (process.env.HERDR_ENV !== "1") {
				try {
					const out = execFileSync("bash", [runSh, base, ...agyArgs], {
						cwd,
						encoding: "utf8",
						timeout: timeoutSec * 1000,
						killSignal: "SIGKILL",
						stdio: "pipe",
					});
					const result = readResult(eventsPath);
					const text = result?.response?.trim() || out.trim() || "(无输出)";
					return {
						content: [{ type: "text", text: `(未在 herdr 中运行，没有独立 tab)\n\n${text}` }],
						details: { status: result?.status, conversationId: result?.conversation_id, logDir: base } as AgyRunDetails,
					};
				} catch (error: any) {
					rmSync(base, { recursive: true, force: true });
					throw new Error(`agy 运行失败（非 herdr 环境）：${error?.message ?? error}`);
				}
			}

			const workspaceId = process.env.HERDR_WORKSPACE_ID;
			if (!workspaceId) throw new Error("HERDR_WORKSPACE_ID 未设置，无法新建 tab");

			let paneId = "";
			try {
				const created = parseHerdrJson(
					herdr(["tab", "create", "--workspace", workspaceId, "--cwd", cwd, "--label", label, "--no-focus"]),
				);
				paneId = created?.result?.root_pane?.pane_id ?? "";
				if (!paneId) throw new Error("tab create 没有返回 root pane id");
			} catch (error: any) {
				rmSync(base, { recursive: true, force: true });
				throw new Error(`创建 herdr tab 失败：${error?.message ?? error}`);
			}

			// 单行命令：脚本走文件，参数逐个单引号包住，避免行编辑器遇到换行
			const inner = ["bash", runSh, base, ...agyArgs].map(shellQuote).join(" ");
			herdr(["pane", "run", paneId, inner]);

			if (params.background) {
				// 后台模式：立刻还回 pane id，跑完由 poller 用 steer 消息唤醒 pi
				pending.set(paneId, { base, paneId, label, deadline: Date.now() + timeoutSec * 1000 });
				ensurePoller(pi);
				return {
					content: [
						{
							type: "text",
							text: `agy 已在 tab ${paneId} 里开始跑（后台模式），跑完会用一条消息把结论送回来。你现在可以继续做别的事。`,
						},
					],
					details: { paneId, background: true } as AgyRunDetails,
				};
			}

			// 完成判定只看 sidecar 文件：agi 的终端输出会滚动、会重绘，不适合解析。
			const deadline = Date.now() + timeoutSec * 1000;
			let lastTick = Date.now();
			while (!existsSync(sidecarPath) && Date.now() < deadline && !signal?.aborted) {
				await sleep(300);
				if (existsSync(sidecarPath)) break;
				if (Date.now() - lastTick >= 5000) {
					lastTick = Date.now();
					const elapsed = Math.round((Date.now() - (deadline - timeoutSec * 1000)) / 1000);
					onUpdate?.({ content: [{ type: "text", text: `agy 在 ${paneId} 里运行中，已 ${elapsed}s…` }] });
				}
			}

			const result = readResult(eventsPath);
			const response = (result?.response ?? "").trim();
			const denied: string[] = (result?.denied_actions ?? []).map((d: any) => d?.display_name || d?.action || "?");
			const ok = result?.status === "SUCCESS" && response.length > 0 && denied.length === 0;

			const meta = [
				`pane ${paneId}`,
				result?.status ? `status ${result.status}` : null,
				result?.conversation_id ? `cid ${result.conversation_id}` : null,
				result?.duration_seconds ? `${result.duration_seconds.toFixed(1)}s` : null,
				denied.length ? `被拒工具 ${denied.join(",")}` : null,
			]
				.filter(Boolean)
				.join(" · ");

			if (ok) {
				// 成功即关 tab，工作区不留垃圾
				try {
					herdr(["pane", "close", paneId]);
				} catch {
					// 关不掉不算失败
				}
				rmSync(base, { recursive: true, force: true });
				return {
					content: [{ type: "text", text: `${response}\n\n[${meta}]` }],
					details: {
						paneId,
						conversationId: result?.conversation_id,
						status: result?.status,
						durationSec: result?.duration_seconds,
						totalTokens: result?.usage?.total_tokens,
						tabKept: false,
					} as AgyRunDetails,
				};
			}

			// 失败/超时：保留 tab 让人回看，事件原文留在 logDir
			const reason = !result
				? signal?.aborted
					? "已中止"
					: `等了 ${timeoutSec}s 没等到结果`
				: denied.length
					? `agy 想调用 ${denied.join(",")} 被权限拒绝（只读模式），需要 -w/write=true`
					: response.length === 0
						? "agy 返回空回复"
						: `agy 报错 ${result.status}`;
			return {
				content: [
					{
						type: "text",
						text: `agy 未成功：${reason}\n${meta}\ntab ${paneId} 保留着，可以用 \`herdr pane read ${paneId}\` 看现场；事件原文在 ${eventsPath}`,
					},
				],
				details: {
					paneId,
					conversationId: result?.conversation_id,
					status: result?.status,
					denied,
					tabKept: true,
					logDir: base,
					error: reason,
				} as AgyRunDetails,
			};
		},
	});
}
