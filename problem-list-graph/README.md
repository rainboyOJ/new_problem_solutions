# problem-list-graph（题单 · 知识点图谱）

一个自包含的静态题单页面：按知识点给洛谷题目分类，支持专题视图、路径视图、速查和模板必背视图，并带**做题进度**与**本站解析入口**。

它是独立模块，不依赖本站的题目数据、内容快照或渲染管线：页面自带样式、脚本和数据，只有一个入口 URL。

- 线上入口：`https://pcs2.roj.ac.cn/problem-list`
- 静态资源：`public/problem-list-graph/`
- 数据导出：`public/problem-list-graph/problems.json`

## 文件

| 文件 | 说明 |
| --- | --- |
| `public/problem-list-graph/index.html` | 自包含页面：数据内嵌，0 处 `fetch`，0 个外部资源（无 CDN、无外链样式）。单文件可直接分发给学生。 |
| `public/problem-list-graph/problems.json` | 同一份数据的机器可读导出，供脚本、AI 和其他前端消费。 |
| `problem-list-graph/build-solutions.py` | 数据脚本：扫 `problems/` 求出「本站有解析」的题号，注入上面两个产物的 `solutions` 字段，并回写本 README 的 `solGenerated` 与 sha256。 |
| `tests/problem-list-graph-solutions.test.js` | 独立复算校验：用页面里的 `keyOf` 重扫一遍 `problems/`，比对 `solutions`；同时校验内嵌 `DATA` 与 README 的 sha256（`npm test`）。 |

当前产物（`generated: 2026-10-08`，`solGenerated: 2026-10-09`）：

```
f266463478d9f83240c56ad33acd709889ef63f1d7ae57101242664e73a039dd  index.html
65f93d281a392a9d3e0b655699b2bb30de8d9f535c1b11f4da7055612f08a1e3  problems.json
```

## 数据契约

`problems.json` 顶层字段：

| 字段 | 说明 |
| --- | --- |
| `generated` | 题单数据的生成日期 |
| `solGenerated` | `solutions` 的生成日期（**只在该数组真的变化时才刷新**，所以重跑脚本不会改字节） |
| `total` | 题目总数（3028） |
| `categories` | 知识点大类 → 子类，各带 `count` |
| `sources` | 题目来源 → `count`（86 个，如「各省省选」「USACO」「NOIP 提高组」） |
| `tierCount` / `tierName` | 难度推荐档位计数与显示名：`T0` 必做、`T1` 强烈推荐、`T2` 推荐、`T3` 进阶 |
| `diffOrder` | 难度排序：入门 → 普及- → 普及/提高- → 普及+/提高 → 提高+/省选- → 省选/NOI- → NOI/NOI+/CTSC |
| `stageOrder` | 训练阶段排序：阶段1 · 语法与模拟 → 阶段5 · NOI / CTSC（另有阶段0 · 未评定） |
| `solutions` | **本站有解析**的题号，形如 `["codeforces/165E", "luogu/P1001", …]`（711 条） |
| `problems` | 题目数组 |

单个题目：

```json
{
  "id": "P1048",
  "name": "[NOIP 2005 普及组] 采药",
  "diff": "普及-",
  "rk": 2,
  "solvers": 120,
  "tier": "T0",
  "stage": "阶段2 · 普及 / CSP-J",
  "cats": [["动态规划", "DP综合"], ["动态规划", "背包DP"]],
  "sources": ["2005", "NOIP 普及组"],
  "tpl": false,
  "url": "https://www.luogu.com.cn/problem/P1048"
}
```

- `cats` 是 `[大类, 子类]` 对，一题可属于多个子类（2246/3028 题多于一个，最多 11 个）。
- `tpl` 标记模板必背题（149 题）。
- 题目编号前缀：`P` 2508、`CF` 293、`AT` 202、`SP` 21、`UVA` 4，共 3028 题。
- `url` 指向原站：`P`/`SP`/`UVA` 走洛谷（2533 题），`CF` 走 codeforces.com（293 题），`AT` 走 atcoder.jp（202 题）。题号与难度仍是洛谷口径。
- 351 题 `cats` 为空（254 题难度 `NOI/NOI+/CTSC`、48 题入门，其余零散），页面按“未归类”处理。

## 进度与解析

### 进度：与题目单共用同一份数据

页面的 checkbox、`xxx / 3028 已完成` 计数与三态筛选（全部 / 未完成 / 已完成）都读写题目单那一个 localStorage key：

| 项 | 值 |
| --- | --- |
| key | `rbook.problem-set.progress`（与 `views/problem-set.pug`、`public/javascripts/problem-set-progress.js` 同一个） |
| 值形状 | `{ "<oj>/<题号>": true }`，例如 `{"luogu/P1001": true}` |
| 完成判定 | 严格 `value === true`；取消勾选是 `delete`，不是写 `false` |
| 写入方式 | read-modify-write，**保留不认识的键**（题目单写进去的 acwing / roj / noi_openjudge / shumeng 进度不能被抹掉） |

键 = `<oj 目录名>/<规范化题号>`，也就是题目单里的 `data-problem-key` = 本站题目路径尾段。页面的 `keyOf(id)`（`index.html` 里 `/* keyOf:start */ … /* keyOf:end */` 之间）负责推导：

| 本题单题号 | `keyOf` 结果 | 说明 |
| --- | --- | --- |
| `P1048` | `luogu/P1048` | 洛谷 `p?数字` 题号补成 `P数字`（对齐 `lib/problem.js` 的 `normalizeProblemId`） |
| `SP1716` | `luogu/SP1716` | 洛谷体系，保留原名 |
| `UVA10298` | `luogu/UVA10298` | 洛谷体系，保留原名 |
| `CF600E` | `codeforces/600E` | 去掉 `CF` 前缀 |
| `AT_agc001_e` | `atcoder/agc001_e` | 去掉 `AT_` 前缀 |

两个方向都成立：在本题单勾选的题，若题目单里也列了它，题目单会显示已完成；反之亦然。注意题目单只为**本站收录**的题生成任务（`lib/problem-set.js` 里非 `/problems/<oj>/<id>` 形式的链接不生成），所以题目单只覆盖本题单 3028 题中的 104 个去重题号，剩下的是本题单单向记录。

不做跨标签页实时同步（与题目单详情页一致），换页签后刷新才看到对方的改动。

### 解析：构建期烘焙，运行期零请求

「本站有解析」= `problems/<oj>/<题号>/index.md` 存在。脚本把命中的题号写进 `solutions`，页面启动时建 `Set`，命中就渲染一个绿色「解析」chip，链接是**相对路径** `/problems/<key>`，新标签打开。

- 命中 711 / 3028（luogu 708、codeforces 3、atcoder 0）。
- 只有 `index.md` 存在才算，所以点进去一定有内容；与本仓库严格一致。

## 与 `problems/` 的关系

题单覆盖**洛谷题号体系下的全域目录**，不是本站收录题的清单：其中 2508 个 `P` 编号里，本站 `problems/luogu/` 目前有 1164 题有 `index.md`。因此：

- 题单**不读** `problems/`、`problem-sets/`，也不进内容快照；页面路由没有 `contentGuard`，内容不可用时它照常提供。
- 反过来，本站在题目单里引用的题目，可以从这份数据查难度、来源和知识点归属。
- `solutions` 是唯一一处从 `problems/` 反查进来的信息，由脚本烘焙，页面不联网。

## 生成与维护

`problems.json` 与 `index.html` 内嵌的 `DATA` 是**同一份字节**，由脚本一起写；UI（CSS、checkbox、进度、三态筛选、解析 chip 的渲染逻辑）是手改在 `index.html` 里的，脚本不碰。

```sh
# 题解新增/删除后重跑（幂等，可重复执行）
python3 problem-list-graph/build-solutions.py
#   → 重写 problems.json 与 index.html 的 DATA
#   → 刷新 README 的 solGenerated 与 sha256
#   → 打印命中数、按 oj 拆分与抽样

# 校验是否漂移（CI / pre-push）
npm test
```

脚本固定顶层字段顺序为 `generated, solGenerated, total, …, stageOrder, solutions, problems`，紧凑单行序列化，所以重跑只要数据没变就是**逐字节相同**。`index.html` 是 CRLF、`problems.json` 无换行符，脚本按字节读写并沿用原换行风格。

## 已知限制

1. **「解析」按钮需要在线访问**。它用的是相对路径 `/problems/<key>`，所以跟着站点部署时完全正常；把 `index.html` 当单文件拷走后以 `file://` 打开，这个按钮会 404（页面其余功能不受影响）。
2. **`SP` / `UVA` 系题号的大小写风险**。`keyOf` 对它们只做前缀替换，而仓库里 `problems/luogu/` 的目录用的是 `uva11572`、`cf19d` 这种小写形式，`normalizeProblemId` 又只规范化 `p?数字`。目前这些题在本站均无收录（0 命中），一旦将来收录，两边进度键会错配——脚本此时会**直接报错退出**并列出冲突题号，强制人工处理。
3. **题目单只覆盖 104 个去重题号**。本题单可勾选全部 3028 题，但题目单里只列了 104 个，其余题目的进度只有本题单看得到。
4. **与题目单的「题解」badge 存在 27 道口径差**。题目单的 badge 判定是「`problems/` 里有该题目录」（`data-problem-exists`），比这里的「有 `index.md`」宽；落在本题单题号域内的这 27 道（`P1290`、`P1399`、`P1659`…）在题目单显示「题解」，这里不显示「解析」。
5. **`solutions` 要手动重跑脚本更新**。新增题解不会自动进数据；`npm test` 会因此失败并提示重跑。

## 维护约定

- 产物按**字节**提交。改数据一律走 `python3 problem-list-graph/build-solutions.py`；不要在 `index.html` 或 `problems.json` 里手改 `solutions` / `solGenerated` / hash。
- 只改 UI（样式、渲染逻辑）时手改 `index.html`，然后重跑一次脚本让它刷新 sha256。
- 页面无外部依赖，改动后仍要保持这一条：不得引入 CDN、外链字体或运行时 `fetch`。
- 部署：`public/` 随 app release 打包（`scripts/build-native-release.sh`），改动会走 application 变更路径重新上传 app release，无需改 `deploy.sh`。
- 那个把知识点大类、`tier` 四档、`stage` 六阶段编排出来的**原始生成器仍然没有入库**（是教练判断，需要人工映射表）。现在提交的是它的产物快照；本文的脚本只负责往里注入 `solutions`。
