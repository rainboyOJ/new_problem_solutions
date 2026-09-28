/**
 * oj-prompt —— 会话内挑一个 prompt 模板，放进输入框再决定发不发。
 *
 * 用法：`/oj-prompt [模板名] [参数...]`
 *   - 只写 `/oj-prompt`：打开选择器（模糊筛选 + 正文预览）
 *   - 第一个词精确匹配某个模板名：跳过选择器，直接用后面的参数渲染该模板
 *
 * 选择器按键：
 *   ↑/↓             移动选择
 *   Enter           插入模板正文（编辑器为空则整段替换，否则追加并折叠成 [paste #n]）
 *   Tab             插入 `@<模板相对路径>` 引用，不展开正文
 *   PgUp/PgDn       滚动正文预览，Home/End 跳到开头/结尾
 *   Esc / Ctrl+C    取消
 *
 * 和内置 `/模板名` 命令的区别：内置命令回车即发送、也没有正文预览；这里只把内容
 * 放进输入框，留给用户改完再回车。参数替换规则（$1 / $@ / ${N:-默认} / ${@:-默认}）
 * 与 pi 的 prompt template 完全一致。
 *
 * 模板从 `pi.getCommands()` 里筛 `source === "prompt"` 得到，因此项目 `.pi/settings.json`
 * 的 `prompts` 和 `--prompt-template` 注册的模板都能看到，与当前 cwd 无关。
 */

import { readFileSync } from "node:fs";
import { relative, sep } from "node:path";
import {
	type ExtensionAPI,
	type ExtensionCommandContext,
	type Theme,
	stripFrontmatter,
} from "@earendil-works/pi-coding-agent";
import {
	type Component,
	Input,
	Key,
	Markdown,
	type MarkdownTheme,
	fuzzyFilter,
	matchesKey,
	truncateToWidth,
	visibleWidth,
} from "@earendil-works/pi-tui";

interface PromptItem {
	name: string;
	description: string;
	path: string;
	body: string;
	scope: string;
}

interface PickResult {
	item: PromptItem;
	mode: "body" | "reference";
}

/** 读取所有可用的 prompt 模板（正文已去掉 frontmatter）。 */
function loadPrompts(pi: ExtensionAPI): PromptItem[] {
	const items: PromptItem[] = [];
	const seen = new Set<string>();
	for (const command of pi.getCommands()) {
		if (command.source !== "prompt") continue;
		if (seen.has(command.name)) continue;
		const path = command.sourceInfo?.path;
		if (!path) continue;
		try {
			const body = stripFrontmatter(readFileSync(path, "utf-8")).trim();
			items.push({
				name: command.name,
				description: command.description ?? "",
				path,
				body,
				scope: command.sourceInfo?.scope ?? "project",
			});
			seen.add(command.name);
		} catch {
			// 读不到的文件直接跳过，不影响其他模板
		}
	}
	return items.sort((left, right) => left.name.localeCompare(right.name));
}

/** 按 shell 风格引号切分参数，和 pi 的 parseCommandArgs 一致。 */
function parseArgs(input: string): string[] {
	const args: string[] = [];
	let current = "";
	let quote: string | null = null;
	for (const char of input) {
		if (quote) {
			if (char === quote) quote = null;
			else current += char;
		} else if (char === '"' || char === "'") {
			quote = char;
		} else if (/\s/.test(char)) {
			if (current) {
				args.push(current);
				current = "";
			}
		} else {
			current += char;
		}
	}
	if (current) args.push(current);
	return args;
}

/**
 * 占位符替换。pi 的 substituteArgs 没有从包入口导出，这里复刻它的语义：
 * $1 $2 / $@ / $ARGUMENTS / ${N:-默认} / ${@:-默认} / ${@:N} / ${@:N:L}
 */
const PLACEHOLDER_RE = /\$\{(\d+|ARGUMENTS|@):-([^}]*)\}|\$\{@:(\d+)(?::(\d+))?\}|\$(ARGUMENTS|@|\d+)/g;

function substituteArgs(content: string, args: string[]): string {
	const allArgs = args.join(" ");
	return content.replace(
		PLACEHOLDER_RE,
		(_match, defaultTarget, defaultValue, sliceStart, sliceLength, simple) => {
			if (defaultTarget) {
				const value =
					defaultTarget === "@" || defaultTarget === "ARGUMENTS"
						? allArgs
						: args[Number.parseInt(defaultTarget, 10) - 1];
				return value ? value : defaultValue;
			}
			if (sliceStart) {
				const start = Math.max(0, Number.parseInt(sliceStart, 10) - 1);
				if (sliceLength) {
					return args.slice(start, start + Number.parseInt(sliceLength, 10)).join(" ");
				}
				return args.slice(start).join(" ");
			}
			if (simple === "ARGUMENTS" || simple === "@") return allArgs;
			return args[Number.parseInt(simple, 10) - 1] ?? "";
		},
	);
}

/** 用当前主题搭一个 Markdown 主题，避免依赖 jiti 下可能未初始化的全局主题。 */
function buildMarkdownTheme(theme: Theme): MarkdownTheme {
	return {
		heading: (text) => theme.bold(theme.fg("accent", text)),
		link: (text) => theme.fg("accent", text),
		linkUrl: (text) => theme.fg("dim", text),
		code: (text) => theme.fg("muted", text),
		codeBlock: (text) => theme.fg("muted", text),
		codeBlockBorder: (text) => theme.fg("dim", text),
		quote: (text) => theme.fg("muted", text),
		quoteBorder: (text) => theme.fg("dim", text),
		hr: (text) => theme.fg("dim", text),
		listBullet: (text) => theme.fg("accent", text),
		bold: (text) => theme.bold(text),
		italic: (text) => theme.italic(text),
		strikethrough: (text) => text,
		underline: (text) => theme.underline(text),
	};
}

/** 把一行左侧文字和右侧文字拼到同一行，宽度按终端列计算。 */
function joinSides(left: string, right: string, width: number): string {
	const leftWidth = visibleWidth(left);
	const rightWidth = visibleWidth(right);
	if (leftWidth + rightWidth + 1 <= width) {
		return left + " ".repeat(width - leftWidth - rightWidth) + right;
	}
	return truncateToWidth(left, Math.max(0, width - rightWidth - 1)) + " " + right;
}

/** 把模板路径显示成相对 cwd 的短路径。 */
function displayPath(cwd: string, target: string): string {
	const rel = relative(cwd, target);
	if (!rel || rel.startsWith("..") || rel.includes(`${sep}..${sep}`)) return target;
	return rel;
}

async function pickPrompt(
	ctx: ExtensionCommandContext,
	prompts: PromptItem[],
	initialQuery: string,
): Promise<PickResult | null> {
	if (ctx.mode !== "tui") {
		ctx.ui.notify("选择器需要交互 TUI；请改用 /oj-prompt <模板名> <参数>", "warning");
		return null;
	}

	return ctx.ui.custom<PickResult | null>(
		(tui, theme, keybindings, done) => {
			const search = new Input({ prompt: theme.fg("accent", " 筛选 ") });
			if (initialQuery) search.setValue(initialQuery);

			let query = initialQuery;
			let filtered = filterItems(prompts, query);
			let index = 0;
			let listTop = 0;
			let previewTop = 0;
			let previewKey = "";
			let previewLines: string[] = [];
			let previewRowCount = 8;

			/**
			 * 两层筛选：先按模板名模糊匹配（和内置 `/` 补全一致），没命中名字的再按
			 * 描述匹配并排在后面。这样既能搜「对拍」这种中文描述，又不会被长描述里
			 * 的英文字母顺序刷出一堆噪音。
			 */
			function filterItems(items: PromptItem[], value: string): PromptItem[] {
				const query = value.trim();
				if (!query) return items;
				const byName = fuzzyFilter(items, query, (item) => item.name);
				const nameHits = new Set(byName.map((item) => item.path));
				const rest = fuzzyFilter(
					items.filter((item) => !nameHits.has(item.path)),
					query,
					(item) => `${item.description} ${item.scope}`,
				);
				return [...byName, ...rest];
			}

			function current(): PromptItem | undefined {
				return filtered[index];
			}

			function resetSelection(): void {
				index = 0;
				listTop = 0;
				previewTop = 0;
				previewKey = "";
			}

			function move(delta: number): void {
				if (filtered.length === 0) return;
				index = (index + delta + filtered.length) % filtered.length;
				previewTop = 0;
				tui.requestRender();
			}

			function confirm(): void {
				const item = current();
				if (item) done({ item, mode: "body" });
			}

			function useReference(): void {
				const item = current();
				if (item) done({ item, mode: "reference" });
			}

			function scrollPreview(delta: number, toEnd = false): void {
				const max = Math.max(0, previewLines.length - previewRowCount);
				previewTop = toEnd ? max : Math.min(max, Math.max(0, previewTop + delta));
				tui.requestRender();
			}

			/** 正文预览按 (路径, 宽度) 缓存；预览的文本和 Enter 插入的完全一致（无参数渲染）。 */
			function getPreview(item: PromptItem, width: number, rows: number): string[] {
				const key = `${item.path}@${width}`;
				if (key !== previewKey) {
					previewLines = new Markdown(
						substituteArgs(item.body, []),
						1,
						0,
						buildMarkdownTheme(theme),
					).render(width);
					previewKey = key;
					previewTop = 0;
				}
				previewRowCount = rows;
				return previewLines;
			}

			const component: Component & { focused: boolean } = {
				// Focusable：把焦点透传给内部 Input，保证中文输入法光标位置正确
				get focused(): boolean {
					return search.focused;
				},
				set focused(value: boolean) {
					search.focused = value;
				},
				invalidate() {
					previewKey = "";
				},
				handleInput(data: string): void {
					const isUp = keybindings.matches(data, "tui.select.up") || matchesKey(data, Key.up);
					const isDown = keybindings.matches(data, "tui.select.down") || matchesKey(data, Key.down);
					const isCancel =
						keybindings.matches(data, "tui.select.cancel") ||
						matchesKey(data, Key.escape) ||
						matchesKey(data, Key.ctrl("c"));

					if (isUp) move(-1);
					else if (isDown) move(1);
					else if (keybindings.matches(data, "tui.select.confirm") || matchesKey(data, Key.enter)) confirm();
					else if (matchesKey(data, Key.tab)) useReference();
					else if (isCancel) done(null);
					else if (matchesKey(data, Key.pageDown)) scrollPreview(previewRowCount);
					else if (matchesKey(data, Key.pageUp)) scrollPreview(-previewRowCount);
					else if (matchesKey(data, Key.home)) {
						previewTop = 0;
						tui.requestRender();
					} else if (matchesKey(data, Key.end)) scrollPreview(0, true);
					else {
						search.handleInput(data);
						query = search.getValue();
						filtered = filterItems(prompts, query);
						resetSelection();
						tui.requestRender();
					}
				},
				render(width: number): string[] {
					const termRows = tui.terminal?.rows ?? 24;
					const inner = Math.max(6, Math.floor(termRows * 0.88) - 8);
					const listRows = Math.min(
						Math.max(1, filtered.length),
						Math.max(3, Math.min(10, Math.floor(inner * 0.35))),
					);
					const previewRows = Math.max(2, inner - listRows);
					const item = current();
					const lines: string[] = [];

					const border = (text: string) => theme.fg("dim", text);
					lines.push(border("─".repeat(Math.max(1, width))));
					lines.push(
						joinSides(
							theme.bold(theme.fg("accent", " OJ prompt")),
							theme.fg("dim", `${filtered.length}/${prompts.length} 个模板 `),
							width,
						),
					);
					lines.push(...search.render(width).map((line) => truncateToWidth(line, width, "", true)));

					if (listTop > index) listTop = index;
					if (index >= listTop + listRows) listTop = index - listRows + 1;
					for (let row = 0; row < listRows; row++) {
						const entry = filtered[listTop + row];
						if (!entry) {
							lines.push("");
							continue;
						}
						const selected = listTop + row === index;
						const marker = selected ? theme.fg("accent", " ❯ ") : "   ";
						const nameWidth = Math.min(24, Math.max(12, Math.floor(width * 0.28)));
						const nameText = truncateToWidth(entry.name, nameWidth, "…");
						const nameField = nameText + " ".repeat(Math.max(1, nameWidth - visibleWidth(nameText)));
						const name = selected ? theme.bold(theme.fg("accent", nameField)) : theme.fg("text", nameField);
						const description = theme.fg("muted", entry.description);
						lines.push(truncateToWidth(marker + name + description, width, "…", true));
					}

					lines.push(border("·".repeat(Math.max(1, width))));

					if (!item) {
						lines.push(theme.fg("warning", " 没有匹配的模板"));
						for (let row = 0; row < previewRows; row++) lines.push("");
					} else {
						const preview = getPreview(item, width, previewRows);
						const max = Math.max(0, preview.length - previewRows);
						previewTop = Math.min(previewTop, max);
						const from = preview.length === 0 ? 0 : previewTop + 1;
						const to = Math.min(preview.length, previewTop + previewRows);
						lines.push(
							joinSides(
								theme.fg("accent", ` 预览 ${item.name}.md`) +
									theme.fg("dim", ` · ${item.scope}`),
								theme.fg("dim", `行 ${from}-${to}/${preview.length} `),
								width,
							),
						);
						for (let row = 0; row < previewRows; row++) {
							lines.push(truncateToWidth(preview[previewTop + row] ?? "", width, "", true));
						}
					}

					lines.push(
						truncateToWidth(
							theme.fg(
								"dim",
								" ↑↓ 移动 · Enter 插入正文 · Tab 插入 @路径 · PgUp/PgDn 看预览 · Esc 取消",
							),
							width,
							"…",
							true,
						),
					);
					lines.push(border("─".repeat(Math.max(1, width))));
					return lines;
				},
			};

			search.onSubmit = confirm;
			search.onEscape = () => done(null);

			return component;
		},
		{
			overlay: true,
			overlayOptions: {
				width: "100%",
				maxHeight: "92%",
				anchor: "center",
				margin: 0,
			},
		},
	);
}

function insertPrompt(ctx: ExtensionCommandContext, result: PickResult, args: string[]): void {
	if (result.mode === "reference") {
		const ref = `@${displayPath(ctx.cwd, result.item.path)}`;
		ctx.ui.pasteToEditor(`${ref} `);
		ctx.ui.notify(`已插入引用 ${ref}`, "info");
		return;
	}

	const text = substituteArgs(result.item.body, args).trimEnd();
	const existing = ctx.ui.getEditorText();
	if (existing.trim().length > 0) {
		// 编辑器已有内容：追加，超长会折叠成 [paste #n]，发送时自动展开
		ctx.ui.pasteToEditor(`\n${text}\n`);
	} else {
		// 空编辑器：整段放进去，便于先看再改
		ctx.ui.setEditorText(`${text}\n`);
	}
	ctx.ui.notify(`已插入 ${result.item.name} 正文，可先编辑再回车发送`, "info");
}

export default function ojPromptExtension(pi: ExtensionAPI): void {
	pi.registerCommand("oj-prompt", {
		description: "选择 OJ prompt 模板并插入输入框（Enter 正文 / Tab @引用）",
		handler: async (argsRaw: string, ctx: ExtensionCommandContext) => {
			const prompts = loadPrompts(pi);
			if (prompts.length === 0) {
				ctx.ui.notify("没有找到 prompt 模板：检查 .pi/settings.json 的 prompts 或 --prompt-template", "warning");
				return;
			}

			const raw = argsRaw.trim();
			const tokens = parseArgs(raw);
			const exact = tokens.length > 0 ? prompts.find((item) => item.name === tokens[0]) : undefined;
			if (exact) {
				// `/oj-prompt <模板名> <参数...>`：跳过选择器，直接渲染
				insertPrompt(ctx, { item: exact, mode: "body" }, tokens.slice(1));
				return;
			}

			const result = await pickPrompt(ctx, prompts, raw);
			if (!result) return;
			insertPrompt(ctx, result, []);
		},
	});
}
