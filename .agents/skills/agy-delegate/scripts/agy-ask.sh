#!/usr/bin/env bash
# agy-ask.sh —— 把 agy 无头模式包成可脚本化的一次问答。
#
# 设计目标是兜住实测出来的三个坑:
#   1. status=SUCCESS 但 response 为空, 真正原因是 denied_actions 非空;
#   2. 不设超时时偶尔单次调用会拖到 100s 以上;
#   3. stderr 的提示混在 stdout 里会污染 JSON。
# 所以默认只读 (不给 --dangerously-skip-permissions), 退出码区分失败原因。
#
# 退出码: 0 成功 / 2 参数错 / 3 工具被拒 / 4 空回复 / 5 agy 报错 / 124 超时

set -uo pipefail

MODEL=""
EFFORT=""
PRINT_TIMEOUT="180s"
OUTER_TIMEOUT="240"
ALLOW_WRITE=0
CONVERSATION=""
RAW=0
PROMPT=""

die() { printf '%s\n' "$2" >&2; exit "$1"; }

usage() {
    cat <<'EOF'
用法: agy-ask.sh [选项] "提示词"

  -m, --model ID        模型 id, 见 agy models (如 gemini-3.8-flash-high, claude-opus-4-6-thinking)
  -e, --effort LEVEL    low|medium|high|xhigh|max; 仅部分模型支持, 不支持会直接报错
  -P, --print-timeout T 传给 agy 的 --print-timeout (默认 180s)
  -T, --timeout SEC     外层 timeout 秒数 (默认 240)
  -c, --conversation ID 续接已有会话
  -w, --write           允许 agy 执行命令/改文件 (加 --dangerously-skip-permissions)
  -r, --raw             原样输出 agy 的 JSON, 不做解析
  -h, --help            显示本帮助

只读模式下 agy 能 view_file / grep_search / list_dir, 但不能 run_command。
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        -m|--model)         MODEL="$2"; shift 2 ;;
        -e|--effort)        EFFORT="$2"; shift 2 ;;
        -P|--print-timeout) PRINT_TIMEOUT="$2"; shift 2 ;;
        -T|--timeout)       OUTER_TIMEOUT="$2"; shift 2 ;;
        -c|--conversation)  CONVERSATION="$2"; shift 2 ;;
        -w|--write)         ALLOW_WRITE=1; shift ;;
        -r|--raw)           RAW=1; shift ;;
        -h|--help)          usage; exit 0 ;;
        -*)                 usage >&2; die 2 "未知选项: $1" ;;
        *)                  PROMPT="$1"; shift ;;
    esac
done

[ -n "$PROMPT" ] || die 2 "缺少提示词 (或用 -p 之外的位置参数给出)"
command -v agy >/dev/null || die 2 "找不到 agy"

CMD=(agy)
# 位置参数与 --print 都太容易吃掉后续 flag, 统一用 -p=值 的写法。
CMD+=("-p=$PROMPT")
CMD+=("--output-format" "json")
CMD+=("--print-timeout" "$PRINT_TIMEOUT")
[ -n "$MODEL" ] && CMD+=("--model" "$MODEL")
[ -n "$EFFORT" ] && CMD+=("--effort" "$EFFORT")
[ -n "$CONVERSATION" ] && CMD+=("--conversation" "$CONVERSATION")
[ "$ALLOW_WRITE" = 1 ] && CMD+=("--dangerously-skip-permissions")

TMP_OUT=$(mktemp)
TMP_ERR=$(mktemp)
trap 'rm -f "$TMP_OUT" "$TMP_ERR"' EXIT

timeout "$OUTER_TIMEOUT" "${CMD[@]}" >"$TMP_OUT" 2>"$TMP_ERR"
RC=$?

if [ "$RC" = 124 ]; then
    printf '超时: agy 在 %ss 内没有返回 (外层 timeout)\n' "$OUTER_TIMEOUT" >&2
    tail -5 "$TMP_ERR" >&2
    exit 124
fi

if [ "$RAW" = 1 ]; then
    cat "$TMP_OUT"
    exit 0
fi

# agy 把提示信息写到 stderr, JSON 在 stdout; 但个别版本会把提示混进 stdout,
# 所以按行挑出第一个能解析的对象。
python3 - "$TMP_OUT" "$TMP_ERR" <<'PY'
import json, sys

out_path, err_path = sys.argv[1], sys.argv[2]
raw = open(out_path, encoding="utf-8", errors="replace").read()
err = open(err_path, encoding="utf-8", errors="replace").read().strip()

payload = None
for line in raw.splitlines():
    line = line.strip()
    if line.startswith("{"):
        try:
            payload = json.loads(line)
            break
        except json.JSONDecodeError:
            continue

if payload is None:
    print("agy 没有输出可解析的 JSON:", file=sys.stderr)
    print(raw.strip()[:2000] or "(stdout 为空)", file=sys.stderr)
    if err:
        print("stderr:", err[:1500], file=sys.stderr)
    sys.exit(5)

status = payload.get("status", "")
denied = payload.get("denied_actions") or []
resp = (payload.get("response") or "").strip()
usage = payload.get("usage") or {}
dur = payload.get("duration_seconds")

def meta():
    bits = [f"status={status}"]
    if dur is not None:
        bits.append(f"{dur:.1f}s")
    if usage:
        bits.append(f"tokens={usage.get('total_tokens')}")
    if payload.get("conversation_id"):
        bits.append(f"cid={payload['conversation_id']}")
    return " ".join(bits)

if status != "SUCCESS":
    print(f"agy 失败 ({meta()}): {payload.get('error') or resp or '(无错误信息)'}", file=sys.stderr)
    if err:
        print(err[:1500], file=sys.stderr)
    sys.exit(5)

if denied:
    names = ",".join(d.get("display_name") or d.get("action", "?") for d in denied)
    print(f"agy 被权限拒绝 ({meta()}): {names}", file=sys.stderr)
    print("只读模式下 agy 不能跑命令; 需要它自己执行命令或改文件时加 -w, 并自行校验副作用。", file=sys.stderr)
    if err:
        print(err[:1500], file=sys.stderr)
    sys.exit(3)

if not resp:
    print(f"agy 返回空回复 ({meta()})", file=sys.stderr)
    if err:
        print(err[:1500], file=sys.stderr)
    sys.exit(4)

print(resp)
print(f"[{meta()}]", file=sys.stderr)

# --json-schema 时 agy 会把结构化结果放在 structured_output;
# 实测它可能只是复述任务而非答案, 所以单独提示, 不替调用方采信。
if payload.get("structured_output") is not None:
    print("structured_output: " + json.dumps(payload["structured_output"], ensure_ascii=False), file=sys.stderr)
PY
