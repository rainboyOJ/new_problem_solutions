#!/usr/bin/env bash
# 把 three.js 的三个运行时文件同步到 public/vendor/three/，
# 并重打 OrbitControls 的裸说明符补丁（改成相对路径，页面就不需要 importmap）。
#
# 用法：./scripts/sync-three-vendor.sh
# 升级 three 依赖后运行一次即可。
set -euo pipefail

repo_root="$(git rev-parse --show-toplevel)"
cd "$repo_root"

src="node_modules/three"
dst="public/vendor/three"

if [ ! -d "$src" ]; then
  echo "找不到 $src，请先 npm install" >&2
  exit 1
fi

mkdir -p "$dst"
cp "$src/build/three.module.js" "$dst/three.module.js"
cp "$src/build/three.core.js" "$dst/three.core.js"
cp "$src/examples/jsm/controls/OrbitControls.js" "$dst/OrbitControls.js"
cp "$src/LICENSE" "$dst/LICENSE"

# three.core.js 是 three.module.js 通过相对路径 './three.core.js' 引入的，
# 两个文件必须放在同一目录，这里不需要改。
#
# OrbitControls 上游写的是 from 'three'（裸说明符），需要 importmap 才能解析。
# 改成相对路径后，页面在任意子目录的 HTTP 环境下都能直接加载。
python3 - "$dst/OrbitControls.js" <<'PY'
import sys
from pathlib import Path

path = Path(sys.argv[1])
text = path.read_text(encoding="utf-8")
needle = "} from 'three';"
replacement = "} from './three.module.js'; // 本地化补丁：把裸说明符 'three' 改成相对路径，免去 importmap"

if replacement in text:
    print(f"{path}: 补丁已存在，跳过")
    sys.exit(0)

count = text.count(needle)
if count != 1:
    raise SystemExit(f"{path}: 期望恰好 1 处 {needle!r}，实际 {count} 处；上游可能改版，请人工检查")

path.write_text(text.replace(needle, replacement), encoding="utf-8")
print(f"{path}: 已打补丁")
PY

version="$(python3 -c "import json,sys; print(json.load(open('node_modules/three/package.json'))['version'])")"
echo "已同步 three.js $version 到 $dst"
