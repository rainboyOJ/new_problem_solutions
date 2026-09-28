#!/usr/bin/env bash
#
# 准备 rbook 仓库级的 pi 配置目录（.pi/agent），供 `rpi` 使用。
#
# 为什么需要它：pi 的项目配置只认 `cwd/.pi/**`，不向上查找。所以在
# `problems/<oj>/<id>/` 里跑普通 `pi` 时，仓库的写题 prompt 模板、`/oj-prompt`
# 扩展和 OJ 助手身份都不会加载。`PI_CODING_AGENT_DIR` 可以把配置目录整体换掉，
# 但它是「替换」而不是「合并」——auth.json、models.json、trust.json、已安装的包
# 都在默认目录（~/.pi/agent）里，所以这里用符号链接把它们共享过来。
#
# 用法：
#   scripts/navi/rpi-agent-setup.sh           # 建符号链接（幂等）
#   scripts/navi/rpi-agent-setup.sh --sync    # 另外把全局 settings 里的
#                                             # packages / 模型 / 主题偏好同步进仓库配置
#
# 之后用 `rpi`（见 scripts/navi/rbook-shell.zsh）在仓库任意目录启动 pi。
#
# 见 docs/tools/rbook-pi.md。
set -euo pipefail

REPO="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
AGENT_DIR="$REPO/.pi/agent"
GLOBAL_DIR="$HOME/.pi/agent"

SYNC=0
case "${1:-}" in
  --sync) SYNC=1 ;;
  -h | --help)
    sed -n '2,25p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    exit 0
    ;;
  "") ;;
  *)
    printf 'rpi-agent-setup.sh: 未知参数 %s（只支持 --sync）\n' "$1" >&2
    exit 2
    ;;
esac

command -v pi >/dev/null 2>&1 || {
  printf 'rpi-agent-setup.sh: 找不到 pi。\n' >&2
  exit 1
}

if [ ! -d "$GLOBAL_DIR" ]; then
  printf 'rpi-agent-setup.sh: 找不到全局 pi 配置目录 %s。\n' "$GLOBAL_DIR" >&2
  exit 1
fi

mkdir -p "$AGENT_DIR"

# 共享全局目录里的运行时数据。已是符号链接或已有同名实体文件就跳过，
# 不去覆盖任何已有内容。
link_shared() {
  local name="$1" target="$GLOBAL_DIR/$1" here="$AGENT_DIR/$1"

  if [ ! -e "$target" ]; then
    printf '  跳过 %-18s （全局目录里没有）\n' "$name"
    return 0
  fi
  if [ -L "$here" ]; then
    printf '  保持 %-18s -> %s\n' "$name" "$(readlink "$here")"
    return 0
  fi
  if [ -e "$here" ]; then
    printf '  保留 %-18s （已存在实体，没动它）\n' "$name"
    return 0
  fi

  ln -s "$target" "$here"
  printf '  链接 %-18s -> %s\n' "$name" "$target"
}

printf '仓库级 pi 配置目录：%s\n' "$AGENT_DIR"
printf '共享 %s 里的运行时数据：\n' "$GLOBAL_DIR"
for name in auth.json models.json models-store.json trust.json npm; do
  link_shared "$name"
done

if [ ! -f "$AGENT_DIR/APPEND_SYSTEM.md" ]; then
  printf '你是一个有用的 OJ 题目解析辅助助手。\n' >"$AGENT_DIR/APPEND_SYSTEM.md"
  printf '  新建 APPEND_SYSTEM.md\n'
fi

if [ "$SYNC" -eq 1 ]; then
  printf '从全局 settings.json 同步 packages / 模型 / 主题偏好：\n'
  RPI_AGENT_DIR="$AGENT_DIR" python3 - <<'PY'
import json
import os
import pathlib

agent_dir = pathlib.Path(os.environ["RPI_AGENT_DIR"])
global_settings_path = pathlib.Path.home() / ".pi" / "agent" / "settings.json"
agent_settings_path = agent_dir / "settings.json"

# 只同步「环境级」的键；仓库自己的键（prompts / extensions / sessionDir 等）保留。
SYNCED_KEYS = [
    "packages",
    "defaultProvider",
    "defaultModel",
    "modelThinkingLevels",
    "theme",
    "hideThinkingBlock",
]

global_settings = json.loads(global_settings_path.read_text(encoding="utf-8"))
agent_settings = json.loads(agent_settings_path.read_text(encoding="utf-8")) if agent_settings_path.exists() else {}

changed = []
for key in SYNCED_KEYS:
    if key not in global_settings:
        continue
    if agent_settings.get(key) != global_settings[key]:
        agent_settings[key] = global_settings[key]
        changed.append(key)

agent_settings_path.write_text(
    json.dumps(agent_settings, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
)
print("  更新的键：" + (", ".join(changed) if changed else "无变化"))
print(f"  写入 {agent_settings_path}")
PY
fi

printf '\n完成。用 `rpi` 启动（见 scripts/navi/rbook-shell.zsh），或手动：\n'
printf '  PI_CODING_AGENT_DIR=%s pi\n' "$AGENT_DIR"
