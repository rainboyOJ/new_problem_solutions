# three.js 本地副本

题解里的交互式 3D 演示（如 `problems/luogu/P4568/layered-water-3d*.html`）从这里加载 three.js，
不再请求 CDN。这样首次打开是毫秒级，断网也能用。

## 文件来源

| 文件 | 来源 |
|---|---|
| `three.module.js` | `node_modules/three/build/three.module.js` |
| `three.core.js` | `node_modules/three/build/three.core.js`（被 `three.module.js` 再 import 一次） |
| `OrbitControls.js` | `node_modules/three/examples/jsm/controls/OrbitControls.js` |
| `LICENSE` | `node_modules/three/LICENSE`（MIT，要求保留版权声明） |

## 相对上游的唯一改动

`OrbitControls.js` 第 12 行的裸说明符 `from 'three'` 改成了 `from './three.module.js'`。
这样页面不需要 `importmap`，也能在 HTTP 下的任意子目录正常解析。

## 更新方式

```bash
./scripts/sync-three-vendor.sh
```

脚本会从 `node_modules/three` 重新拷贝上面三个文件，并自动重打那一行补丁。
升级 `three` 依赖后运行一次即可。

## 注意

浏览器在 `file://` 下会按 CORS 规则拒绝加载本地 `.js` 模块。
演示页请通过站点地址访问（`/problems/<oj>/<id>/xxx.html`），不要直接双击 HTML 文件。
直接双击时页面会显示一句明确提示，不会白屏。
