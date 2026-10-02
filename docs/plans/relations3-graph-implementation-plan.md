## relations3-graph 实施规划

状态：已按阶段实现，源码、构建产物及验证流程已接入。实际测试、浏览器验收和性能结果见 [验收记录](./relations3-graph-validation.md)。下文保留已确认的产品决策与实施基线。

编写日期：2026-10-02。仓库核对基线：`1ec39666`；本地参考库核对基线：`8c301c7`。实现前检查当前代码差异，以实际代码和用户后续指令为准。

目标：在现有题目关系数据上新增独立的 3D 关系图，让读者围绕一道题，准确辨认直接前置、直接后续和相似题目，并沿着关系连续探索。

### 交接给实现者的指令

可以直接将下面这段指令交给 GPT 6.1 Sol：

```text
请按照 docs/plans/relations3-graph-implementation-plan.md 实现 relations3-graph。

用户已经确认本文“已确认的产品决策”，直接按开发阶段推进，不必重复产品访谈。
先读 AGENTS.md、CONTEXT.md，以及本文列出的现有代码入口。
本地 /home/rainboy/__git__/react-force-graph 只用于参考源码和示例。
正式安装 react-force-graph-3d 等 npm 依赖，固定直接依赖版本并更新 lockfile。
新增 /relations3，保留 /relations 和 /relations2 及其现有入口。

交付范围是完整可用的新页面。先做核心阅读体验验证，再补齐原有功能，
不能以一个只能显示球和线的演示页面作为完成结果。
尤其保证：选题和搜索不重排；前置方向正确；一层关系与侧栏一致；
探索返回可用；3D 坐标独立保存；真实 npm 构建和项目验证覆盖新版。

本文中的初始数值和模块拆分可以根据实测调整，但不能擅自缩减确认的功能。
对库 API 以实际安装版本的类型声明和源码为准，不照搬 2D 专用接口。
完成后报告代码改动、测试结果、浏览器验收记录及尚未解决的限制。
不要自行提交、推送或部署。
```

本文中的代码片段是接口与算法示意，尚未经过目标依赖版本的编译验证；实现者需要将它们补成真实模块并运行检查。

## 1. 已确认的产品决策

下表记录已经完成的访谈结论，后续实现以此为产品基线。

| 决策 | 确认内容 |
| --- | --- |
| 首要目标 | 关系可读性；优先读懂某一道题的周边关系 |
| 展示维度 | 真正的 3D 关系图，使用三维坐标与可旋转相机 |
| 聚焦范围 | 默认只突出中心题与一层直接关系，不自动追溯完整前置链 |
| 背景 | 其他可见节点和边淡化，保留网络上下文 |
| 相机 | 选中题目后平滑聚焦，容纳它的一层邻居，尽量保持当前观察方向 |
| 布局 | 切换中心时保持已有节点位置，不按前置、后续、相似关系重新分区 |
| 标签 | 中心题显示题号与完整标题；邻居显示题号与短标题，悬停补全；背景隐藏标签 |
| 连续探索 | 点击邻居切换中心，只突出新中心的一层关系，提供返回上一个题目的操作 |
| 普通入口 | 显示关系网络总览，默认隐藏孤立题目，通过点击或搜索选中心 |
| 题目入口 | 从题目页进入时直接聚焦 URL 中指定的题目 |
| 侧栏 | 按前置题、后续题、相似题列出具体题目和已有关系说明；可切换中心，也可打开题解 |
| 功能范围 | 保留搜索、关系筛选、孤立题目开关、拖拽固定和保存、刷新、重新布局、主题与直达链接 |
| 设备 | 桌面优先；手机支持触摸浏览、点选及关系清单 |
| 版本关系 | `/relations`、`/relations2`、`/relations3` 并存，新增“3D 关系图”入口 |
| 库的使用方式 | 本地仓库只作参考；应用使用锁定版本的 `react-force-graph-3d` npm 包 |

用户确认的是以上行为。本文后续的文件拆分、缓存格式、相机动画时长、颜色和性能建议属于实现方案，可以在保持这些行为的前提下调整。

一期不增加关系元数据编辑、自动推荐关系、VR/AR、2D/3D 切换、自动旋转、粒子流和泛光效果。拖拽只改变本地显示位置，不写入题目内容。

## 2. 先阅读哪些现有代码

先理解以下入口，再开始新增文件；不要根据文件名猜测框架或接口。

| 现有入口 | 实现时需要提取的事实 |
| --- | --- |
| [CONTEXT.md](../../CONTEXT.md) | 题目、前置关系、相似关系、孤立题目的领域定义 |
| [relations2 的设计记录](../adr/0003-separate-relations2-canvas-graph.md) | 旧版行为与当时的验收意图；其中数量是历史值 |
| [App.tsx](../../relations2-graph/src/App.tsx) | 数据获取、搜索、筛选、URL、主题、缓存和页面控制 |
| [graph-data.ts](../../relations2-graph/src/graph-data.ts) | 数据归一化、查询匹配、可见节点规则、指纹 |
| [types.ts](../../relations2-graph/src/types.ts) | API 节点、边和统计信息的字段 |
| [layout-core.ts](../../relations2-graph/src/layout-core.ts) | 旧版二维布局与固定坐标；不能直接当三维布局使用 |
| [layout-runner.ts](../../relations2-graph/src/layout-runner.ts) | 旧版 Worker 生命周期与主线程回退 |
| [PixiCanvas.tsx](../../relations2-graph/src/PixiCanvas.tsx) | 旧版画布组件对页面暴露的操作边界 |
| [lib/problem.js](../../lib/problem.js) 的 `getRelationGraph()` | 前置方向、相似关系去重、API 标签颜色和节点 URL 的来源 |
| [routes/api.js](../../routes/api.js) | 复用 `/api/relations`，不另造关系 API |
| [routes/index.js](../../routes/index.js) | Fastify 页面路由与 `guard` |
| [views/relations2.pug](../../views/relations2.pug) | 宿主页的 CSS、JS 与 root 元素接入 |
| [views/layout.pug](../../views/layout.pug)、[views/problem.pug](../../views/problem.pug) | 全站导航和题目页入口 |
| [package.json](../../package.json)、[Vite 配置](../../relations2-graph/vite.config.ts) | 根目录统一依赖、构建命令、固定资源文件名 |
| [scripts/verify-push.js](../../scripts/verify-push.js) | 当前只对第一版关系图做临时构建和产物比对，需要扩展 |
| [tests/fastify-app.test.js](../../tests/fastify-app.test.js) | 现有页面、API 与静态资源测试写法 |
| [tests/pre-push-tooling.test.js](../../tests/pre-push-tooling.test.js) | 验证脚本的已有测试 |

先复用业务规则，不把 Pixi 绘制器、二维坐标类型、旧版 Worker 协议复制过来改名字。第一版实现允许把小型数据纯函数复制到新版并补测试，避免为了共用几段代码重构两个旧页面；不要让新版运行时直接依赖旧版 `App`。

### 已知核对限制

编写本文时工作区缺少 `fastify` 等运行依赖，尝试读取运行时 `/api/relations` 未能启动。因此本文不宣称当前有多少有效节点，也不复用旧 ADR 中的 `117/2139` 作为当前规模。实现者安装依赖后，应从真实 API 重新记录节点数、边数、最大度数和混合关系样例。

当前本机 Node 为 `v25.8.0`，仓库 CI 使用 Node 22。新增测试和工具必须兼容仓库声明的 Node 22，不依赖只在本机新版本存在的 TypeScript 原生执行行为。

## 3. 依赖与构建方案

### 3.1 依赖边界

直接运行依赖预计需要：

- `react-force-graph-3d`：React 组件入口。
- `three`：应用自定义节点材质、关系线和相机计算所直接使用的依赖。
- `three-spritetext`：如采用 Sprite 标签，直接声明这个依赖。
- `d3-force-3d`：如按本文加入三维碰撞力，直接声明这个依赖，不依赖传递安装碰巧可用。

按实际类型声明补齐 `@types/three`、`@types/d3-force-3d` 等开发依赖；先检查包是否已经内置类型。不要盲目安装重复类型包。

实现时查询各包版本、peerDependencies 和 engines，选择兼容 React 19、当前 Vite 和 Node 22 的组合，再使用 `npm install --save-exact` 固定直接依赖版本。同步更新 `package-lock.json` 并纳入交付。本地参考仓库根包版本不是独立 `react-force-graph-3d` 包的版本，不能直接挪用。

检查 `npm ls three`，尽量保证绘图库与自定义对象使用兼容的 Three.js 实例。不要在页面中通过 CDN、import map 或 Babel standalone 运行官方 HTML 示例。

### 3.2 新版构建

新增 `relations3-graph/vite.config.ts`，沿用旧版配置模式并替换以下值：

```text
root: relations3-graph
base: /relations3-graph/
outDir: public/relations3-graph
entryFileNames: assets/index.js
assetFileNames: assets/[name][extname]
manifest: true
dev proxy /api -> http://127.0.0.1:3000
```

输出目录必须独立，`emptyOutDir` 只能清理新版自己的目录。源码入口、独立开发 HTML 和 Pug 宿主页都使用 `relations3-root`。

根 `package.json` 增加如下脚本；名称在下文测试命令中保持一致：

```json
{
  "build:relations3": "vite build --config relations3-graph/vite.config.ts",
  "typecheck:relations3": "tsc --noEmit -p relations3-graph/tsconfig.json",
  "build": "npm run build:relations && npm run build:relations2 && npm run build:relations3"
}
```

`vite build` 不替代 TypeScript 类型检查。继续使用根目录依赖，不新建一套嵌套 npm 工程和 lockfile。

## 4. 文件划分与职责

下面是建议的源码布局。可合并很小的文件，但不要把布局、相机、数据归一化和侧栏全部写进一个 `App.tsx`。

```text
relations3-graph/
  index.html
  vite.config.ts
  tsconfig.json
  src/
    main.tsx                  # root、StrictMode、样式入口
    App.tsx                   # 数据加载及各功能模块编排
    types.ts                  # 业务类型、三维坐标、视图状态
    graph-data.ts             # API 归一化、搜索、可见范围、指纹
    relation-index.ts         # 前置/后续/相似索引与一层关系
    exploration.ts            # 中心题及返回历史的纯 reducer
    url-state.ts              # URL 参数解析与序列化
    layout-store.ts           # 三维位置校验、加载、保存
    graph-model.ts            # 业务对象 -> 可变引擎对象；保留对象身份
    layout-policy.ts          # 何时允许模拟、冻结、恢复与重新布局
    camera.ts                 # 聚焦位置、取景范围与退化处理
    Graph3D.tsx               # 库适配、生命周期、事件与命令句柄
    graph-objects.ts          # Three.js 节点、关系线、材质和资源释放
    label-manager.ts          # 标签内容、可见性、投影与避让
    Toolbar.tsx               # 搜索、筛选、刷新与布局控制
    DetailsPanel.tsx          # 题目详情和三类关系清单
    Legend.tsx                # 关系线、节点颜色及选中状态说明
    styles.css                # r3 命名空间、桌面/手机布局
    vite-env.d.ts
  tests/
    graph-data.test.js
    relation-index.test.js
    exploration.test.js
    graph-model.test.js
    camera.test.js
    layout-store.test.js
    url-state.test.js
views/
  relations3.pug
public/
  relations3-graph/            # 构建生成，不手改
```

上述测试文件不要求为了凑目录全部建立空壳；按后文有实际风险的行为编写。新增模块使用 TypeScript，保留严格类型检查。

## 5. 数据结构与关系语义

### 5.1 三层对象必须分开

区分 API 业务数据、页面视图状态和力导向引擎对象。引擎会写入坐标，也可能将边的 `source/target` 从字符串改成节点对象；不能让这种修改污染业务关系索引和缓存指纹。

下面的类型表达边界。业务字段参照现有 `RelationNode/RelationEdge`，不重复设计另一套 API。

```typescript
interface Position3D {
  x: number;
  y: number;
  z: number;
}

interface SimNode extends Position3D {
  id: string;
  vx?: number;
  vy?: number;
  vz?: number;
  fx?: number;
  fy?: number;
  fz?: number;
}

interface SimLink {
  id: string;
  source: string | SimNode;
  target: string | SimNode;
  sourceId: string;
  targetId: string;
  type: 'pre' | 'common';
}

interface FocusNeighborhood {
  centerId: string;
  nodeIds: Set<string>;
  edgeIds: Set<string>;
  predecessors: RelationEntry[];
  successors: RelationEntry[];
  commons: RelationEntry[];
}

interface RelationEntry {
  nodeId: string;
  edgeId: string;
  reason: string;
}
```

`sourceId/targetId` 是应用保存的不可变业务端点；关系判断只使用这两个字段或原始边，绝不对已经被库修改的 `source` 调用字符串方法。

在 `graph-model.ts` 中维护 `Map<string, SimNode>` 和 `Map<string, SimLink>`。相同 ID 复用现有对象、坐标与速度，新增节点才初始化位置，删除节点才清理。选中、悬停、主题改变时不重新 `map()` 整张图生成引擎对象。

### 5.2 归一化规则

- 保留合法且唯一的节点 ID，校验节点 OJ、题号等必要字段。
- 只接受 `pre/common`，未知关系类型不自动当成 `pre`；丢弃并记录可诊断数量。
- 丢弃端点不存在的边，以免布局库报找不到节点。
- 按边 ID 去重；相似关系不自行补成两条相反方向的边。
- 从保留下来的边重新计算计数与孤立状态，避免归一化后统计仍引用已被丢弃的边。
- 保留 API 给出的 `color` 和 `tagStats` 色彩映射，避免重排标签统计后重新分配颜色导致图例不一致。
- 搜索覆盖 OJ、题号、显示名、标题、难度和标签，沿用大小写不敏感的包含匹配。

这些是新版数据层的改进，不要求同时修复旧版数据层。

### 5.3 一层关系的准确含义

对于中心 `C`：

- `pre: A -> C`：A 是前置题。
- `pre: C -> B`：B 是后续题。
- `common: C -- D` 或 `D -- C`：D 是相似题；存储端点顺序不表示方向。
- 高亮节点为中心与以上直接邻居，高亮边仅为中心直接关联的边。
- 两个邻居之间的边仍属背景，不能因为两端都高亮就自动将它也高亮。
- 同一道题可能同时出现在多个关系组中，不强行给它指定唯一角色；图上只有一个节点，侧栏可分别出现。

索引在数据加载或刷新后构建一次。选择中心后按其相邻边取结果，避免每帧扫描全部节点、全部边。

### 5.4 筛选、搜索与中心题的优先级

默认 `pre/common` 都开启；紧凑视图保留当前启用关系类型的端点。孤立开关开启时展示全部有效题目。搜索匹配项和有效中心题即使不在紧凑网络中，也可临时展示。

三类侧栏与一层高亮服从当前边筛选，组标题显示当前可见数量；若另列全量数量，必须标明“全部关系”，避免两种计数混用。

中心题的高亮优先于搜索淡化规则：搜索不能把正在阅读的中心和邻居一起变暗。总览中搜索匹配项突出，非匹配项淡化；聚焦中额外提示匹配项，但不会把它们当成中心题的邻居。点击搜索结果才切换中心。

两种边都关闭时，保留中心、搜索匹配项或明确开启的全部节点，侧栏提示当前筛选未显示关系。合法孤立题可以被搜索、URL 直达和选中，三个关系组为空，不报告“题目不存在”。

## 6. 页面状态与连续探索

### 6.1 状态边界

React 状态保存业务结果和交互状态；连续变化的坐标、Three 对象和每帧参数保存在 ref/引擎对象中。不要每帧把整张坐标表写入 React state。

至少区分以下状态：

```text
data / loadStatus / loadError / refreshing
query / showPre / showCommon / showIsolated
selectedId / history / historyCursor
hoveredNodeId / hoveredEdgeId
layoutStatus / renderStatus / renderError
dark / mobileDetailsOpen
```

布局失败、数据失败和 WebGL 失败分别处理。刷新失败保留上一份可用图并显示错误，不把整个图清空。

### 6.2 统一选题入口

所有选题动作进入同一个 `selectNode(id, origin)`。`origin` 可以是图节点、搜索结果、侧栏或 URL；业务效果一致。

处理顺序：验证 ID -> 更新中心与历史 -> 推导一层关系 -> 更新视觉 -> 在模型准备好之后发出相机聚焦请求 -> 更新 URL。相机请求带递增序号，旧动画或异步加载结果不能覆盖后来选中的题目。

历史至少提供“返回上一个题目”；不必为了历史功能更换前端路由框架。

- 总览可作为 `selectedId = null` 的历史项。
- 选中不同题目才追加历史，重复点击当前题目可重新取景，不追加重复项。
- 从历史中间选新题，截断后面的分支。
- 返回操作移动历史游标，不再向历史追加新项。
- 当前题目被刷新删除时退出聚焦并给出提示，历史中不存在的题目在返回时跳过。
- 可保存每一历史项离开前的相机位置与目标，以便返回时恢复观察角度；没有有效快照时重新计算该题取景。

历史只在当前页面会话有效；浏览器刷新后恢复 URL 中的中心题，不承诺恢复完整探索历史。

### 6.3 URL 协议

沿用 `oj/pid/edges/isolated` 参数，读写集中在 `url-state.ts`：

```text
/relations3
/relations3?oj=luogu&pid=P1968
/relations3?oj=luogu&pid=P1968&edges=pre
/relations3?edges=none&isolated=1
```

未提供 `edges` 表示两类都开启；`edges=none` 表示两类都关闭；`isolated=1` 表示全部题目。使用 `URLSearchParams` 编码，不拼接未经编码的题号。

使用 `history.replaceState` 保持地址同步，应用自己的“返回上一题”管理探索历史；不要直接用 `window.history.back()` 冒充上一题。监听必要的 `popstate` 同步 URL，但不要创建相互触发的更新循环。

数据尚未加载时保留待解析的 URL 中心，不提前判断不存在。未知题目加载完成后给出说明并回到可浏览总览。

## 7. 三维布局与位置稳定

### 7.1 初始策略

使用库内置的三维 d3 引擎，设置 `numDimensions=3`、连接力、斥力和三维碰撞力。首次布局使用有限的模拟步数和运行时间，收敛后停止物理模拟，但继续允许相机与鼠标交互。

初始化坐标应覆盖三维空间，而不是把旧版 `x/y` 复制后统一补 `z=0`。可用节点 ID 加布局种子生成确定性的球面/球体散点，再由力导向收敛；三个坐标始终是有限数。显示孤立题目时给它们独立的初始空间，避免全部堆在原点。

可用 `cooldownTicks`、`cooldownTime` 和 `onEngineStop` 管理模拟结束；具体初始值集中放在配置常量中，依据真实数据调整。不要用 `pauseAnimation()` 代替停止物理模拟，否则可能连相机动画和交互渲染一起暂停。

三维碰撞力从 `d3-force-3d` 获取并核对实际类型接口；不要把二维 `d3-force` 的碰撞函数直接当成三维使用。碰撞半径覆盖节点球体和少量间距，标签重叠单独处理。

不启用 `dagMode`：全图含无向相似关系，不能假设全部边构成 DAG。前置关系的方向由箭头和侧栏表达。

### 7.2 何时允许位置改变

实现 `layout-policy.ts`，将视觉变化与拓扑变化分开。下面的行为表用于防止看似普通的 React 更新触发全图重新模拟。

| 动作 | 节点位置策略 | 相机策略 |
| --- | --- | --- |
| 首次进入且无有效缓存 | 有限模拟，结束后固定当前结果 | 总览取景或 URL 中心取景 |
| 相同拓扑恢复有效缓存 | 直接恢复，无须再次自动重排 | 按入口状态取景 |
| 悬停、主题、标签变化 | 坐标不变 | 不动 |
| 输入或清空搜索 | 已有节点坐标不变 | 不自动移动 |
| 选中节点、点击侧栏、历史返回 | 已有节点坐标不变 | 聚焦目标或恢复历史视角 |
| 切换边筛选/孤立开关 | 优先恢复已有坐标；新增节点初始化 | 不强制每次全图 fit |
| 拖拽 | 用户明确移动的节点改变；拖后固定 | 不额外抢占镜头 |
| 刷新但拓扑未变 | 保留位置与固定状态 | 保留视角 |
| 刷新后拓扑变化 | 保留旧位置作为初值；必要时有限模拟，尊重用户固定节点 | 中心仍存在则保留阅读目标 |
| 点击“重新布局” | 清除当前图的固定状态与位置，重新模拟 | 完成后按中心或总览取景 |

过滤产生的显隐变化不是“重新布局”命令。新显示的节点可以使用缓存位置或稳定种子的三维位置，已有节点不需要跟着移动。

### 7.3 引擎数据更新的具体实现约束

维护独立的拓扑签名、布局参与集合和当前显示集合。查询与中心题不进入“是否应该重新模拟”的签名。

普通中心切换只更新材质、标签和相机，不更换 `graphData`。优先保留已经进入引擎模型的节点，通过 `nodeVisibility/linkVisibility` 或自定义对象可见性控制显示。

显隐不会自动改变物理计算集合。明确重新布局时，连接力只作用于启用的关系，斥力、居中力和碰撞力只针对本轮布局参与节点。可在适配层用只初始化参与节点的力包装器实现，并透传三维引擎的初始化参数；保留但隐藏的节点固定在原坐标。不要仅设置 `visible=false`，却让隐藏边继续拉动可见节点，或让大批隐藏孤立题影响居中。

紧凑网络之外的搜索匹配节点或孤立中心可能需要第一次加入引擎，此时：

1. 保存并冻结已有节点坐标；新增节点使用缓存或确定性的三维位置。
2. 在布局已经停止的模式下协调模型更新，例如将模拟步数设为零，并临时给节点设置 `fx/fy/fz`。
3. 更新模型后验证旧节点坐标未改变，再处理相机请求。
4. 引擎因 `graphData` 变化自行重新加热时，也不能产生实际的整体位移。

库版本如何响应 `cooldownTicks=0`、对象显隐和 `refresh()`，必须通过原型确认；它们不能仅凭名字被当成稳定性保证。必要时保留临时冻结坐标直到下一次明确允许布局的事件。

区分 `userPinnedIds` 和为了稳定显示暂时冻结的节点。缓存只将用户拖拽产生的固定状态标为用户固定，不把整个图误存成永久固定。

### 7.4 拖拽处理

库的默认拖拽会重新激活模拟，需要与上述策略协调。推荐拖拽开始时临时固定其他节点，拖拽结束时把该节点的 `fx/fy/fz` 设为当前 `x/y/z`，加入用户固定集合，并防抖保存。

坐标直接读取节点对象，不依赖拖拽事件第二个参数一定声明了 `z`。本地参考库中事件说明与类型声明在这方面存在差异，应以实际包验证。

拖拽手势结束不能再次触发点击选题并突然移动相机；验证库是否已经抑制 click，必要时通过拖拽标志或阈值处理。

### 7.5 Worker 的边界

首版先验证内置布局，不能宣称它自动继承了旧版的 Worker 隔离。如果真实数据布局明显阻塞交互，再增加三维 Worker：Worker 输出三维坐标，主线程组件冻结为结果坐标，避免两个模拟引擎同时运行。

Worker 是基于测量的后备实现，不应在第一个可读性原型之前重写全部布局基础设施。发现性能不达标时必须记录并处理，不能把“当前能显示”当成通过。

## 8. 相机聚焦的代码设计

### 8.1 取景对象

聚焦集合是当前中心与筛选后的一层邻居，不包括搜索匹配但不相邻的题，也不包括全图所有可见节点。以中心题坐标作为 `lookAt`，保证中心题仍是阅读焦点。

使用中心为球心、包住一层邻居的球计算安全距离，保留屏幕留白。不要固定写 `distance=40`，也不要照搬示例中以节点相对世界原点的向量计算镜头位置的做法；节点可能就在原点。

下面的纯函数算法可放进 `camera.ts`，用测试覆盖几何边界：

```text
center = 中心题三维坐标
direction = normalize(当前 camera.position - 当前 controls.target)
direction 长度过小时，回退到预设观察方向 (0, 0, 1)

radius = max(distance(center, 每个聚焦节点) + 该节点显示半径)
radius = max(radius, 最小单题取景半径)

verticalHalfFov = 相机有效垂直视场角 / 2
horizontalHalfFov = atan(tan(verticalHalfFov) * 画布宽高比)
limitingHalfFov = min(verticalHalfFov, horizontalHalfFov)
distance = radius / sin(limitingHalfFov) * 留白系数
distance = max(distance, radius + nearPlane + 安全距离)

newCameraPosition = center + direction * distance
lookAt = center
```

读取透视相机实际参数；如 camera 类型只暴露基类，在适配器中检查并收窄为 `PerspectiveCamera`。`camera.zoom` 不为 1 时使用有效 FOV，不能始终读取裸 `fov`。

### 8.2 动画和控制

- 使用公开的 `cameraPosition(position, lookAt, transitionMs)`；动画初始建议 450–700 ms，根据体验调整。
- 相机控制建议选择 `orbit`，保持可理解的上下方向；验证旋转、平移和缩放手势。
- 读取 `controls().target` 时在适配层做最小类型收窄，不向整个页面传播 `any`。
- 相机动画中用户开始操作时应能接管；连续选题只让最后一次选择决定最终镜头。
- 首次 URL 聚焦要等节点坐标与画布尺寸有效，再取景；相机不能先 fit 总览后被多个 effect 来回拉动。
- 初始布局未结束时选题，优先冻结当前结果后聚焦，避免目标继续漂移。
- 检查 near/far plane，保证邻居不会被裁剪。遇到过大跨度时合理调整裁剪范围。
- 尊重 `prefers-reduced-motion`，缩短或关闭程序动画。

“适应视图”在聚焦态适应中心及邻居，在总览态适应当前可见集合；“返回总览”清除中心并适应总览；“重置视角”恢复默认观察方向，不删除位置缓存；“重新布局”才重算节点位置。四者不能共用一个清空所有状态的函数。

### 8.3 画布尺寸

桌面优先把侧栏作为独立布局列，让画布的宽度就是实际可用宽度。工具栏占位也要明确，不能以整个 window 宽度计算取景，却让右侧邻居被详情面板遮住。

使用 `ResizeObserver` 读取 stage 尺寸，再传入组件的 `width/height`。手机详情抽屉打开时，应缩小有效视口或在取景计算中扣除遮挡区域。画布尺寸为零时不进行相机除法计算。

## 9. 节点、关系线与标签

### 9.1 节点视觉

节点球体底色沿用 API 的主标签颜色。中心题和邻居通过外圈、亮度或适度尺寸变化突出；不能为了前置/后续角色覆盖全部标签配色而让图例失真。

建议优先级：中心 > 悬停对象 > 直接邻居 > 额外搜索匹配 > 背景。背景保持淡化但可点击；筛选隐藏的对象不应被拾取。

节点和边对象的创建回调保持稳定，通过 ID 查对象并更新其材质/标签属性。不要让回调依赖每次变化的 `selectedId`，导致库将每次选题理解成全量对象替换。若必须调用 `refresh()`，先验证它在安装版本中是否重新创建对象或触发布局，并让缓存和布局策略承担相应保护。

`nodeOpacity` 是全局值，不能凭空写成每节点回调来实现背景淡化。需要按节点控制透明度时，使用自定义 Mesh 材质。共享球体几何；材质可以按颜色和显示状态缓存，改变共享材质时注意不要同时改掉其他角色的节点。

透明背景节点通常需要关闭 `depthWrite`，否则可能在看起来很淡时仍遮住前景。验证前后球体、关系线和标签的深度表现。

### 9.2 关系线

保留可独立于颜色辨认的关系语义：

- `pre`：实线和方向箭头；箭头从前置题指向后续题。
- `common`：无向虚线，不添加箭头。
- 中心的入边和出边可以采用不同强调色，图例分别标为“前置题 → 当前题”“当前题 → 后续题”。总览中的 `pre` 使用统一样式。
- 悬停关系线显示类型与已有 reason，reason 为空时只显示类型，不编造解释。

本地 API 表和官方文档都将 `linkLineDash` 标为 2D 专用，不能直接传给 3D 组件。3D 关系线建议通过 `linkThreeObject` 创建 `Group`，通过 `linkPositionUpdate` 更新几何。相关 API 参见 [3D 组件文档](https://github.com/vasturiano/3d-force-graph#api-reference)。

具体实现分工：

1. `createLinkObject(edge)` 为边创建可复用对象。相似边使用 `LineDashedMaterial`；前置边使用实线和锥形箭头。
2. `updateLinkGeometry(object, start, end, edge)` 更新位置缓存、虚线距离和箭头朝向。正确处理零长度边；将端点裁剪到节点球体表面附近。
3. 相似边更新顶点后调用 `computeLineDistances()`，否则虚线长度可能不正确。
4. `linkPositionUpdate` 按所安装版本约定返回已处理标志，避免自定义坐标又被默认对象变换二次处理。
5. 自定义箭头时关闭内置方向箭头，避免同一条边显示两套箭头。
6. 同一对节点存在不同类型或相反方向的边时，使用稳定的轻微弧线/偏移分开。自定义几何必须自己实现曲线，不能假定 `linkCurvature` 会替你弯曲自定义对象。

原生 WebGL `Line` 的 `linewidth` 在常见浏览器中不能可靠加粗，不把它作为唯一高亮手段；可用颜色、透明度与箭头尺寸，确实需要粗线再采用适当几何或宽线实现。

### 9.3 标签策略

推荐 `three-spritetext` 的 billboard 标签，让文字朝向镜头；使用 `nodeThreeObject` 组合球体和标签，资源统一交给对象管理器维护。接口参考本地 `example/text-nodes/index-3d.html`，不要照搬它为所有节点始终创建可见文字的策略。

内容规则：

- 中心：OJ/题号与完整标题，可以分行，不截断完整信息。
- 直接邻居：OJ/题号与短标题；截断优先按 Unicode 字符处理，避免截坏中文或 emoji。
- 背景：不显示常驻标签，悬停可显示完整提示。
- 悬停邻居：显示完整标题，不切换中心，不移动镜头。
- 手机：通过点选和侧栏获取完整信息，不依赖不存在的 hover。

应给总览保留寻找入口：远景不铺满标签，近景可显示少量不冲突题号，悬停显示完整信息，搜索结果始终可用。

标签避让是屏幕空间问题，不能只依赖三维碰撞力。只对当前中心、悬停和邻居的候选标签做投影，按优先级贪心保留不相交的矩形；中心标签优先。拥挤时可暂时隐藏冲突的邻居标签，但节点和侧栏条目必须保留全部关系，悬停仍可补全。

将相机变化或节点变化作为标签投影更新的触发条件，使用一个受控 rAF 或控制器事件，避免每帧触发 React 渲染。可按距离调整 Sprite 尺寸保持可读字号，但限制尺寸范围，防止远处标签覆盖大半屏幕。

标题、标签、reason 都是文本。React 文本正常转义；若库的 tooltip 参数按 HTML 解释，先转义或改用受控 DOM 提示，不能把源文本直接拼成 HTML。

### 9.4 GPU 资源所有权

`graph-objects.ts` 管理自己创建的 geometry/material/texture 和 Sprite 资源。卸载、数据删除或真正替换资源时释放；每次悬停只改显示属性，不重建整张场景。

共享资源释放要有明确的统一生命周期，不能删除一个节点就释放所有节点仍在使用的球体几何。库负责自己创建的对象，应用负责自己创建的对象，防止重复释放和泄漏。

## 10. 侧栏、工具栏与移动端

### 10.1 侧栏

`DetailsPanel` 接收中心业务节点、三组关系条目、节点索引和回调，不直接读取 Three.js 场景。

展示题号、标题、标签、难度、当前关系数量，以及三个带标题的题目清单。每个条目有清晰分开的“切换到此题”和“打开题解”操作；不要在一个点击区域里嵌套互相抢事件的链接和按钮。

中心没有某种关系时显示该组为空；筛选关闭时说明被筛选隐藏。已有 reason 原样展示为文本，较长说明可折叠。节点在多个组中出现时保留对应关系说明。

鼠标悬停侧栏条目可同步强调图中对应节点和关系线，移出时恢复当前中心状态，不改变历史。键盘焦点也应有相同的可辨认反馈。

### 10.2 工具栏

保留搜索、pre/common 筛选、显示孤立题目、刷新、适应视图、重置视角、重新布局，并新增返回上一题和返回总览。

搜索结果来自全量有效题目。可以分页或限制首屏条数，但应显示匹配总数和继续查看方式，不把被截断的结果当成无结果。搜索输入时不得反复抢焦点、重排或移动镜头。

提供明确的打开中心题题解入口。若继承旧版双击打开题解，需在适配层实现点击/双击区分并验证库当前事件接口；不要虚构 `onNodeDoubleClick` 属性。手机不依赖双击进入题解。

键盘可操作搜索、筛选、历史和侧栏条目，缩放按钮提供 aria-label。快捷键在输入框、文本域和可编辑元素中不触发。

### 10.3 响应式与主题

CSS 使用 `.relations3-*` 和 `--r3-*` 命名空间，避免修改全局按钮或覆盖旧版画布样式。响应 `document.documentElement.dataset.bsTheme`，主题变化同时更新 CSS、画布背景、材质和标签，不重建布局。

手机采用可折叠工具栏和底部详情抽屉，图形浏览与清单滚动不互相抢手势。验证触摸旋转、捏合缩放、点选、返回与打开题解。首版可以只在桌面提供精确拖拽固定；手机仍须完成基本阅读任务。

## 11. 三维位置持久化

与旧版使用独立命名空间，例如 `rbook.relations3.layout.v1`，不要读取或覆盖 `rbook.relations2.positions.*`。

建议保存如下数据，并在序列化时只提取数字坐标与 ID：

```typescript
interface SavedLayout3D {
  version: 1;
  layoutVersion: number;
  fingerprint: string;
  updatedAt: number;
  positions: Record<string, Position3D>;
  userPinnedIds: string[];
}
```

不要直接 `JSON.stringify(graphData)`：引擎对象可能含对象引用、循环、Three 对象或无需持久化的速度字段。

指纹依据排序后的合法节点 ID、边 ID、端点及关系类型生成。标题、reason 或主题变化不应使布局失效。缓存格式版本和布局算法版本分开，以便未来有针对性地失效。

读取时验证对象结构、版本、节点是否仍存在、`x/y/z` 是否是有限数，过滤已删除 ID。错误 JSON、浏览器禁用存储或配额耗尽不能阻止页面继续工作。

相同指纹直接恢复坐标。数据变更时可从最近一份有效缓存按 ID 迁移仍存在的位置，新节点单独初始化；不得把旧节点映射到另一个题目。建议采用当前指纹快照加最近缓存指针，只保留少量本应用的历史快照，避免无限增长。

布局停止、拖拽结束后保存，防抖初始值可以沿用 250 ms。卸载或 pagehide 时清理计时器并尝试保存最新稳定结果。不要在每个渲染帧写 localStorage。

“重新布局”清空当前有效数据的缓存与用户固定集合，并生成新的布局种子；避免使用同一确定性种子让重新布局每次得到完全相同的结果。普通恢复和临时新增节点仍使用稳定种子保证位置可预测。

## 12. 生命周期与异常状态

`Graph3D` 建议暴露小型命令句柄，由页面调用，不让页面直接操纵场景中的任意对象：

```typescript
interface Graph3DHandle {
  focusNode(id: string): void;
  fitVisible(): void;
  resetView(): void;
  relayout(): void;
  getPositions(): Record<string, Position3D>;
}
```

严格区分组件挂载、模型可用、布局稳定和 WebGL 可用。第一次 mount 后 ref 存在，不代表所有节点已具有合法三维坐标。

需要覆盖的生命周期：

- React StrictMode 的挂载、清理、再次挂载，不能重复监听或泄漏场景。
- 数据请求取消或请求序号，避免先发后到的响应覆盖新数据。
- ResizeObserver、主题 MutationObserver、控制器事件、rAF 和计时器在卸载时清理。
- 窗口变化和抽屉展开后的尺寸更新。
- WebGL 初始化异常、渲染过程中 context lost 和重试。

当 WebGL 不可用时保留 DOM 搜索与分组关系清单，支持切换中心、打开题解、重试，并提供 `/relations2` 回退链接。重试通过真正重建渲染组件或 context 恢复流程进行，不只是清空错误字符串。

没有关系网络时解释开启孤立题目可浏览全部目录。API 无数据、API 失败、当前筛选无边、中心题被删除分别给出相应说明。

不自动轮询数据。仅首次进入或用户点击刷新读取关系 API，以免用户正在探索时图不断变化。

## 13. 路由、导航和构建产物接入

### 13.1 服务端与模板

在 `routes/index.js` 按 `/relations2` 的写法新增 `/relations3`，复用同一个内容 `guard`，使用 `relations3.pug` 和“3D 题目关系图”标题。

`relations3.pug` 继承 `layout.pug`，添加 `relations3-root`，引用：

```text
/relations3-graph/assets/index.css
/relations3-graph/assets/index.js
```

在全站导航与题目页并列增加“3D 关系图”；题目页带编码后的 `oj/pid`。保留旧链接、文本及目标地址。首页不是单页应用，不需要增加 React Router。

按照现有仓库约定生成并纳入 `public/relations3-graph/` 的构建产物。不能只新增源码而使 Pug 引用 404。检查 manifest、动态 chunks 和任何额外资源一并输出，避免漏交依赖块。

### 13.2 验证流程补全

当前 `scripts/verify-push.js` 中 `GENERATED_DIR` 和 `runBuildCheck()` 只覆盖 `relations-graph`。将其改为明确的构建目标列表：

```text
build:relations  -> public/relations-graph
build:relations2 -> public/relations2-graph
build:relations3 -> public/relations3-graph
```

每个目标分别构建到临时目录，与相应已提交产物比对，最后清理临时目录。错误信息必须包含失败目标与应更新的目录，不能全部提示第一版。

把新版 typecheck 纳入 `verify:push`，同时使新增的核心测试进入 `npm test`。`.github/workflows/verify.yml` 已调用 `verify:push`，通常不需要复制第二套 CI 流程。

新增检查首次暴露旧版产物过期时，核对并重新生成对应产物；不要为了消除错误关闭检查或顺便重构旧版。更新验证脚本的现有测试，保证失败阶段与清理行为仍然正确。

## 14. 自动化测试与浏览器验收

### 14.1 核心纯函数测试

继续使用 `node:test` 和 `node:assert/strict`。为 JS 测试导入 TypeScript 纯函数，建议添加锁定版本的 `tsx` 开发依赖，使用下列脚本；避免依赖 Node 25 才有的行为：

```json
{
  "test:relations3": "node --import tsx --test relations3-graph/tests/*.test.js",
  "test": "node --test tests/*.test.js && npm run test:relations3"
}
```

只从测试导入纯函数模块，不从 `Graph3D.tsx` 导入整个浏览器/WebGL 依赖树。也可以采用仓库当时已有的兼容执行方案，但不得复制一份实现到测试中验证自身。

构造小图作为主要夹具：`A -> C -> B`，`C -- D`，`A -- D`，再加一个孤立节点 `E` 和一个同时具有多种关系的节点。它应验证：

1. C 的前置为 A、后续为 B、相似为 D；箭头方向不反转。
2. A 与 D 均高亮时，`A -- D` 不因两端高亮而自动成为 C 的直接高亮边。
3. common 的端点顺序不影响分组；重复边、无效端点、未知类型得到一致处理。
4. 关闭某类边后，图、侧栏与计数一致；中心和合法孤立题不会凭空丢失。
5. 同一节点的多个角色保留，各组 reason 对应正确边。
6. 引擎把 source/target 换成对象后，业务索引、指纹与保存逻辑仍正确。
7. 选中、搜索、主题变化不会重新创建已有 SimNode 或改变其坐标；临时加入孤立节点不移动旧节点。
8. 历史返回、重复选择、分支选择、刷新删除历史题目处理正确。
9. 相机计算覆盖中心在原点、单节点、坐标重合、横屏/竖屏、无效尺寸和大跨度邻居，结果均有限且能容纳球体。
10. 损坏缓存、非有限坐标、版本不匹配、配额异常、节点增加/删除均有安全退路。
11. URL 默认值、`edges=none`、特殊字符题号、未知题目与往返序列化正确。

测试稳定的关系和几何不变量，不对随机力导向布局的具体小数坐标做快照断言。

### 14.2 服务端集成测试

扩展 `tests/fastify-app.test.js`，验证：

- `/relations3` 和带参数地址返回正确宿主页、root、CSS/JS 引用。
- 导航同时存在三个入口，题目页新版链接带正确参数。
- `/api/relations` 协议和两个旧页面保持可用。
- 新版入口 JS/CSS 真实可获取，类型正确，避免只断言 HTML 中出现链接。
- 内容不可用时新版遵守与旧版相同的 guard。

构建产物测试使用生成后的真实输出，不在测试里伪造一个空的 `index.js` 来让资源检查通过。

### 14.3 浏览器功能验收

自动化测试不能证明 3D 图可读。至少完成一次真实桌面浏览器验收和一次手机视口/触摸验收；条件允许时使用真实手机。已有浏览器自动化工具可复用；环境无法打开浏览器时明确报告未验收项目，不能写成全部完成。

实现后将实际结果填写到同目录的 `relations3-graph-validation.md`，记录日期、commit、浏览器、设备/GPU、视口、DPR、数据规模与操作步骤。测试样例从真实 API 中选取，记录题目 ID，方便重复比较。

至少验证以下场景：

| 场景 | 观察结果 |
| --- | --- |
| 无参数进入 | 有关系题总览，孤立开关默认关闭，可搜索与选题 |
| 题目页直达 | 正确中心、完整标签、一层关系与相机取景 |
| 多种关系混合 | 入边、出边、相似边与侧栏逐项一致 |
| 高度数节点 | 邻居未遗漏，标签拥挤可处理，侧栏可完整查阅 |
| 连续选 A、B、C 再返回 | 返回到 B，节点没有全图重排，相机目标正确 |
| 搜索与清空 | 匹配可辨认、中心不丢失、节点不跳动 |
| 关闭两类边再恢复 | 当前状态可解释，没有恢复错误箭头或陈旧清单 |
| 搜索/直达孤立题 | 可选中、侧栏为空且解释正确 |
| 拖拽后刷新浏览器 | 三维位置及用户固定状态恢复 |
| 重置视角与重新布局 | 两种操作行为明确不同 |
| 切换主题、调整窗口、打开手机抽屉 | 图、文字、尺寸与取景同步 |
| 网络失败与再次刷新 | 保留可用数据，错误可重试 |
| WebGL 失败或 context lost | 可使用关系清单，重试能真正重建图形 |
| 连续进出页面与反复选题 | 无明显 WebGL context、事件和材质资源累积 |

重点任务：给出一道真实题，让读者找出一个前置题、一个后续题和一个相似题，阅读关系原因，进入其中一题，再返回。与 `/relations2` 对照记录错误、遮挡及所需操作；只展示一张“看起来不错”的截图不算可读性验收。

### 14.4 性能测量

分别测默认关系网络、开启全部孤立题目后的当前目录，以及构造的高度数中心压力样例。真实数据数量随内容变化，记录实测数量，不写死历史规模。

记录首次可交互耗时、布局耗时、旋转/缩放帧率、选题反馈、长任务及明显资源增长。帧率应在拖动旋转等操作期间取一段样本，不能只看静止后的一个 FPS 数字。

初始工程目标参考旧版意图：桌面默认网络尽量接近 60 FPS，全目录交互争取至少 30 FPS，关注超过 100 ms 的主线程阻塞。这些是待在明确设备上验证的目标，不是已达成的性能承诺，也不放进依赖硬件的 CI 硬阈值。

若未达目标，依次检查全量标签、每帧 React 更新、对象重复创建、过高 DPR、过细几何、持续未停的模拟，再决定是否需要 Worker。任何降级都不能删除关系数据或破坏基本点击与侧栏能力。

### 14.5 最终命令

在仓库根目录执行。安装、首次构建应在资源集成测试之前完成；完整验证通过后，除非有新改动，不重复跑一轮相同检查。

```bash
npm run typecheck:relations3
npm run build
npm run verify:push
```

扩展后的 `verify:push` 应涵盖核心测试、类型检查、三个构建产物比对、内容检查和真实服务健康检查。开发过程中可以使用 `npm run test:relations3`、单个 Node 测试文件和 `npm run build:relations3` 定位问题。

## 15. 按阶段实施与完成条件

下面的阶段是工作拆分建议，不代表本次规划已经授权自动提交 Git commit。

### 阶段 1：工程接入与数据正确性

新增依赖、目录、配置、宿主页、路由、构建脚本；实现归一化与关系索引。使用真实 API 显示基础 3D 节点与边。

完成条件：构建与 typecheck 通过；三个页面并存；关系索引测试通过；记录当前真实规模。先确认实际安装版本的接口与本地参考源码的差异。

### 阶段 2：核心阅读体验

实现稳定的引擎对象、有限模拟、一层高亮、相机聚焦、标签和分组侧栏；将图、搜索结果和侧栏统一到选题入口。加入返回历史。

完成条件：真实混合关系题和高度数题可以完成阅读任务；中心切换不重排；背景淡化、相似虚线和前置箭头正确；快速连续选题最终镜头不出错。

这个阶段解决可读性，而不是先堆齐按钮再处理读不清的图。

### 阶段 3：补齐功能与稳定性

完成筛选、孤立题目、搜索、URL、三维持久化、拖拽固定、重置操作、数据刷新、主题、手机基本操作与异常回退。补齐 StrictMode 和 GPU 资源清理。

完成条件：本文功能表全部可用；刷新恢复、拓扑变更、缓存损坏、无 WebGL 和网络失败有明确行为；旧版仍正常。

### 阶段 4：验证与交付

扩展测试和验证脚本，构建三个版本，更新生成产物，运行最终检查，填写浏览器与性能验收记录。

完成条件：交付差异同时包含源码、依赖锁、模板/路由、测试/验证接入和必要构建产物；报告实际执行的命令与结果、浏览器观察和剩余限制。未执行的检查必须明说。

## 16. 实现时最容易踩的坑

- 把 `relations3` 理解成“第三版二维图”，遗漏已经确认的 3D。
- 每次选题重新创建 `graphData`，导致全图重新模拟。
- 在 effect 中持续调用 fit，把用户旋转、缩放后的视角不断抢回去。
- 将 common 的存储顺序误当学习方向，或者把前置箭头画反。
- 用高亮节点集合推导所有内部边，使中心的一层高亮混入邻居之间的关系。
- 把搜索结果当邻居，导致相机取景范围突然扩大到全图。
- 将所有标签始终显示，或只处理世界坐标碰撞却不处理投影遮挡。
- 直接使用 2D 的 `linkLineDash`、`centerAt`、`zoom` 或画布绘制回调。
- 对全局 `nodeOpacity/linkOpacity` 传入不存在的逐对象回调。
- 把 `pauseAnimation()` 当成“停止布局”，连交互画面也停了。
- 认为库自带三维布局就自带 Worker，忽略主线程布局开销。
- 序列化引擎数据或复用旧二维缓存，产生循环引用或缺失 z。
- 将临时冻结全部保存成用户固定，之后新增数据永远无法正常布局。
- 在一条边或一个节点删除时释放仍被其他对象共享的几何/材质。
- 用 CSS 面板盖住画布，却仍按整个窗口计算相机取景。
- 只新增 `build:relations3`，遗漏主构建、生成产物和 pre-push 检查。
- 在本机 Node 25 上测试通过，却引入 Node 22 无法运行的测试命令。

## 17. 参考库的阅读路径

本地参考目录：`/home/rainboy/__git__/react-force-graph`。这条路径只用于开发查阅，不得进入应用 import、Vite alias、生产配置或 npm `file:` 依赖。

优先查看：

```text
README.md                                      # API 的 2D/3D 支持列
src/packages/react-force-graph-3d/index.js       # 公开绑定的方法
src/packages/react-force-graph-3d/index.d.ts     # ref、节点、边与回调类型
example/click-to-focus/index.html               # cameraPosition 的基本调用
example/text-nodes/index-3d.html                # Sprite 标签组合
example/fix-dragged-nodes/index.html            # fx/fy/fz 固定节点
example/large-graph/index.html                  # 大图示例入口
```

这些示例用于理解调用方式；其中的默认镜头算法、CDN、全量标签和全局脚本不直接作为项目实现。尤其 `example/highlight/index.html` 在本地核对版本使用的是 2D 组件，迁移其“邻居集合”的想法即可，不复制 Canvas API。

在线核对入口：[React 组件官方仓库](https://github.com/vasturiano/react-force-graph)、[3D 组件官方仓库](https://github.com/vasturiano/3d-force-graph)、[底层 Three 图对象官方仓库](https://github.com/vasturiano/three-forcegraph)。最终编码以安装版本的公开接口、类型声明和对应源码为准，不假设本地 checkout、线上主分支与 npm 包始终相同。
