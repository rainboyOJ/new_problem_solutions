#!/usr/bin/env bash
#
# rbook 写题专用 pi 启动器。
#
# 预置 OJ 助手身份（--append-system-prompt），用 fzf 挑一个 prompt 模板
# （scripts/navi/rbook-pi-prompt/*.md，右侧可预览全文），再以 @ 引入对话，
# 用户的选项和消息原样接在末尾。最后进交互 TUI，不带 -p。
#
# 模型、thinking 等级进 TUI 后用 ctrl+l / shift+tab 改；扩展正常加载。
#
# 见 docs/tools/rbook-pi.md。
set -euo pipefail

PROMPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)/rbook-pi-prompt"
SYSTEM_PROMPT='你是一个有用的OJ题目解析辅助助手'
NO_TEMPLATE='（不用模板）'

usage() {
  cat <<'EOF'
Usage:
  rbook-pi.sh [pi 选项...] [消息...]

预置参数，进交互模式：

  pi --append-system-prompt "你是一个有用的OJ题目解析辅助助手" @<选中的模板> [你的选项...] [你的消息...]

流程：

  1. fzf 从 scripts/navi/rbook-pi-prompt/*.md 里选一个 prompt 模板，
     右侧预览模板全文，选「（不用模板）」则不加载模板。
  2. 选中的模板用 @ 引入对话（模板内容在消息最前面）。
  3. 你的选项和消息原样接在末尾，pi 照常解析。

Examples:
  rbook-pi.sh                                   # 选模板，直接开工（按 cwd 干活）
  rbook-pi.sh "问题的输入规模最大是 1e5"          # 选模板 + 补一句上下文
  rbook-pi.sh -c                                # 接着上次会话
  rbook-pi.sh -p "review problems/luogu/P1001"  # 想一次性跑完就自己传 -p

Notes:
  - 脚本不问模型和 thinking：进 TUI 后用 ctrl+l 选模型、shift+tab 调 thinking，
    ctrl+s 存成默认。
  - 不带 -ne，全局扩展（subagents、web access 等）正常加载。
  - 标准输入原样留给 pi；pi 在当前目录运行，不会自动切换目录。
  - fzf 里按 Esc 取消会以 130 退出，不会启动 pi。
EOF
}

die() {
  printf 'rbook-pi.sh: %s\n' "$1" >&2
  exit "${2:-1}"
}

case "${1:-}" in
  -h | --help)
    usage
    exit 0
    ;;
esac

command -v pi >/dev/null 2>&1 || die "找不到 pi。"
command -v fzf >/dev/null 2>&1 || die "找不到 fzf。"

# 候选行：<文件名 — frontmatter description> \t <模板绝对路径>。
# fzf 用 --with-nth=1 只显示 tab 前的 label，输出里仍带 tab 后的路径。
# 最后一行是「不用模板」，value 为空。
template_rows() {
  local file name desc
  for file in "$PROMPT_DIR"/*.md; do
    [ -e "$file" ] || continue
    name="$(basename "$file" .md)"
    desc="$(awk '/^description:/{sub(/^description:[ \t]*/, ""); print; exit}' "$file")"
    printf '%s — %s\t%s\n' "$name" "$desc" "$file"
  done
  printf '%s\t\n' "$NO_TEMPLATE"
}

if ! pick="$(
  template_rows | fzf --delimiter=$'\t' --with-nth=1 --nth=1 --no-multi \
    --layout=reverse --header-first \
    --border --border-label ' 写题模板 ' --info=inline \
    --header '选 prompt 模板（右侧预览全文，Esc 取消）' \
    --preview 'cat {2}' --preview-window 'right:60%:wrap'
)"; then
  exit 130
fi
if [ -z "$pick" ]; then
  exit 130
fi

template="$(printf '%s' "$pick" | cut -f2)"

args=(--append-system-prompt "$SYSTEM_PROMPT")
if [ -n "$template" ]; then
  args+=("@$template")
fi

printf 'rbook-pi.sh: template=%s\n' "${template:-$NO_TEMPLATE}" >&2
exec pi "${args[@]}" "$@"
