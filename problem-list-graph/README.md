# problem-list-graph（题单 · 知识点图谱）

一个自包含的静态题单页面：按知识点给洛谷题目分类，支持专题视图、路径视图、速查和模板必背视图。

它是独立模块，不依赖本站的题目数据、内容快照或渲染管线：页面自带样式、脚本和数据，只有一个入口 URL。

- 线上入口：`https://pcs2.roj.ac.cn/problem-list`
- 静态资源：`public/problem-list-graph/`
- 数据导出：`public/problem-list-graph/problems.json`

## 文件

| 文件 | 说明 |
| --- | --- |
| `public/problem-list-graph/index.html` | 自包含页面：数据内嵌，0 处 `fetch`，0 个外部资源（无 CDN、无外链样式）。单文件可直接分发给学生。 |
| `public/problem-list-graph/problems.json` | 同一份数据的机器可读导出，供脚本、AI 和其他前端消费。 |

当前产物（`generated: 2026-10-08`）：

```
de21a2f8c2a2748dfb69106e96aa0e100a44c0d7cc13b7334c57147762e6b8e2  index.html
9b34d07ef98e6fe1ee2d150696ba873216dfd58cafd7fe32dbee1d521ba57085  problems.json
```

## 数据契约

`problems.json` 顶层字段：

| 字段 | 说明 |
| --- | --- |
| `generated` | 生成日期 |
| `total` | 题目总数（3028） |
| `categories` | 知识点大类 → 子类，各带 `count` |
| `sources` | 题目来源 → `count`（86 个，如「各省省选」「USACO」「NOIP 提高组」） |
| `tierCount` / `tierName` | 难度推荐档位计数与显示名：`T0` 必做、`T1` 强烈推荐、`T2` 推荐、`T3` 进阶 |
| `diffOrder` | 难度排序：入门 → 普及- → 普及/提高- → 普及+/提高 → 提高+/省选- → 省选/NOI- → NOI/NOI+/CTSC |
| `stageOrder` | 训练阶段排序：阶段1 · 语法与模拟 → 阶段5 · NOI / CTSC（另有阶段0 · 未评定） |
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

## 与 `problems/` 的关系

题单覆盖**洛谷题号体系下的全域目录**，不是本站收录题的清单：其中 2508 个 `P` 编号里，本站 `problems/luogu/` 目前有 1160 题。因此：

- 题单**不读** `problems/`、`problem-sets/`，也不进内容快照；页面路由没有 `contentGuard`，内容不可用时它照常提供。
- 反过来，本站在题目单里引用的题目，可以从这份数据查难度、来源和知识点归属。

## 生成器：缺失，待补

**仓库里没有生成脚本，磁盘上也没有找到**（全盘检索 `tierCount`、`知识点图谱` 无命中）。现在提交的是产物快照。

已确认的事实与未知项：

- 可从洛谷取的：`id`、`name`、`diff`、`rk`、`url`、`sources`（题目标签/来源）。
- 疑似人工编排、无法自动推导的：11 个大类 / 约 100 个子类的知识点归类、`tier` 四档推荐、`stage` 六阶段。这些看起来是教练判断，生成器需要把它们作为**输入**（映射表）而不是算出来。
- 语义未知：`solvers` 既不是洛谷通过人数（A+B Problem 是 147），也不是本站数据，来源待查。

补生成器时的目标形态（对齐 `relations3-graph/`）：

1. 在本目录放取数与渲染脚本：拉洛谷元数据 + 读人工编排映射表 → 产出 `problems.json` 与 `index.html`。
2. 页面模板化：`index.html` 由模板 + 内嵌数据渲染，不再手改。
3. 产物提交策略：产物保持入库（本目录 README 记录 sha256），生成器就位后可在 `build-native-release.sh` 里改为构建期重建。

## 维护约定

- 产物按**字节**提交，不改内容；重新生成后必须更新本 README 的 sha256 和 `generated`。
- 页面无外部依赖，改动后仍要保持这一条：不得引入 CDN、外链字体或运行时 `fetch`。
- 部署：`public/` 随 app release 打包（`scripts/build-native-release.sh`），改动会走 application 变更路径重新上传 app release，无需改 `deploy.sh`。
