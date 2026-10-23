## 题目关联下拉菜单与版本化地址

2026-10 （本次变更）：导航栏把原来的「关系图」(`/relations`) 与「关系全景」(`/relations4`) 两个平级入口合并为一个「题目关联」下拉菜单，并把四个关系图版本全部恢复上线。本文替代 [关系图默认入口迁移](./relations-default-3d.md) 中「`relations-graph/`、`relations2-graph/` 不再编译、不再提供服务」的结论；那份记录保留为历史演进过程。

### 决策

| 决策点 | 结论 |
| --- | --- |
| 菜单范围 | 四个版本全部进入「题目关联」下拉，各自可直达 |
| 菜单文案 | `v1 基础版` / `v2 加速版` / `v3 立体版` / `v4 全景版` |
| 地址方案 | 统一为 `/relations/<版本号>`，旧地址 308 重定向 |
| 导航结构 | 删除「关系图」「关系全景」两个平级入口，只留下拉 |
| 下拉交互 | 触发器只负责展开（`<button class="nav-link dropdown-toggle">`），不跳转；当前版本项 `active` + `aria-current="page"` |
| 宿主页 | 四个版本都用 pug 薄壳继承 `layout.pug`，保持站点导航一致 |
| 页面标题 | `关系图 vN · 描述` |
| 题目页入口 | 「关系图」按钮直达 `/relations/3?oj=…&pid=…`，不再经重定向 |
| 验证覆盖 | 与 v3/v4 平级：构建、类型检查、路由冒烟、`verify:push` 构建产物一致性 |

### 页面与资源

| 地址 | 行为 |
| --- | --- |
| `/relations/1` | 渲染 `relations1.pug`，加载 `relations-graph` 产物（SVG 力导向） |
| `/relations/2` | 渲染 `relations2.pug`，加载 `relations2-graph` 产物（PixiJS canvas + worker 布局） |
| `/relations/3` | 渲染 `relations3.pug`，加载 `relations3-graph` 产物（Three.js 3D），默认版本 |
| `/relations/4` | 渲染 `relations4.pug`，加载 `relations4-graph` 产物（canvas 全景与分层） |
| `/relations`、`/relations/`、`/relations3`、`/relations3/` | 308 到 `/relations/3`，查询参数原样保留 |
| `/relations4`、`/relations4/` | 308 到 `/relations/4`，查询参数原样保留 |
| `/relations-graph/*`、`/relations2-graph/*` | 恢复正常提供 JS、CSS 与构建产物 |
| `/relations/<其它值>` | 404 |

所有版本页都经过同一个内容快照 guard：内容不可用时返回 503 + `Retry-After`。重定向本身不读内容快照，因此内容不可用时旧地址照常跳转。

深链接参数在四个版本中各自沿用原有语义：`?oj=&pid=` 聚焦题目，`edges=pre,common|none`、`isolated=1`、`layout=`（v1）、`view=layers`（v4）。

### 代码改动

- `app.js`：删除 fastify-static 里屏蔽 `relations-graph/`、`relations2-graph/` 的 `allowedPath` 白名单。产物重新可访问，因此退役判断只保留在路由层。
- `routes/index.js`：用 `RELATIONS_PAGES` 表注册四个版本页（含尾斜杠变体），用 `LEGACY_RELATIONS_URLS` 表注册 308 重定向；视图本地变量 `relationsVersion` 供导航高亮。
- `views/layout.pug`：导航改为「题目关联」下拉；用 `relationsVersion` 决定触发器 `active` 与菜单项 `aria-current="page"`。触发器用 `<button>` 而不是 `href="#"`，与仓库「页面内不得出现空锚点」的既有约束一致。
- `views/relations1.pug`、`views/relations2.pug`：新增薄壳页；`relations3.pug`、`relations4.pug` 保持原样，标题改由路由传入。
- `views/problem.pug`：题目页「关系图」按钮指向 `/relations/3`。
- `lib/preview-app.js`：预览应用不渲染关系图，四个版本地址与旧地址都重定向回当前预览题目。
- `package.json`：新增 `build:relations`、`build:relations2`、`typecheck:relations`、`typecheck:relations2`；`build` 依次编译四个版本。
- `scripts/verify-push.js`：`RELATION_BUILDS` 扩到四个目标，类型检查阶段按 v1–v4 命名。
- `scripts/build-native-release.sh`：发布前循环构建并复制四个版本的产物。
- `.gitignore`：新增 `public/relations-graph/`、`public/relations2-graph/`。
- 浏览器检查脚本与新地址对齐：`relations3-browser-check.js` 走 `/relations/3`，`relations4-browser-check.js` 走 `/relations/4`；前者原来断言旧产物 404，现在改为断言 v1/v2 产物可访问。
- `relations-graph/src/styles.css`：v1 原来把自己铺成 `position: fixed; inset: 0` 的独立页，嵌入站点后会盖住导航（下拉菜单点不到）。改成与 v2 一致的嵌入方式：`inset: 56px 0 0`，并用 `body:has(#relations-graph-root)` 只对 v1 页取消 `main` 内边距、隐藏页脚并锁滚动。
- `relations2-graph/src/App.tsx`：工具栏「旧版关系图」和两处降级链接原来指向 `/relations`（会 308 到 v3），改指 `/relations/1`。
- `relations4-graph/src/App.tsx`：页内「3D 视图 ↗」由 `/relations` 改为 `/relations/3`，不再经重定向。

### 验证

- `node --test tests/*.test.js`：223 项通过，含新增的「四版本宿主页」「下拉菜单结构」「旧地址 308 保留查询串」「v1/v2 产物恢复可访问」「四个版本都受内容 guard 保护」。
- `npm run test:relations3`（19 项）、`npm run test:relations4`（5 项）通过。
- `npm run build` 产出四个版本的 `public/*-graph/`。
- `node --test tests/pre-push-tooling.test.js`：20 项通过，覆盖四目标的构建脚本与类型检查阶段。
- `npm run verify:push`：9 个阶段全部通过（依赖、测试、v1–v4 类型检查、四目标构建产物一致性、内容索引、真实服务健康）。
- 浏览器端到端脚本（`check:relations3:browser` / `check:relations4:browser`）本次未运行，需要本机 Chromium；脚本地址已同步更新。另用 Playwright + 本机 Chromium 手动核对了导航下拉在浅色/深色下的展开与高亮、v1 与 v2 页面在导航下方正常渲染（v1 修复前 `.react-flow__pane` 会拦截导航点击）。

### 已知差异

- `relations-graph`（v1）是固定浅色配色，不响应站点深浅主题；进入 v1 时深色模式下仍是浅色界面。作为「基础版」保留现状，未做主题适配。
- v1 未做移动端抽屉式布局，触屏体验弱于 v3/v4。
