# 题解可视化辅助规范

题解可以使用 Mermaid、Graphviz、`tree_draw.py`、Markdown 表格和图片解释样例数据或算法过程。可视化的目标是帮助读者更快理解题目，不是装饰页面。

如果需要为某道题生成样例可视化脚本，使用 `oj-sample-visualizer`。它会在当前题目目录生成题目专用脚本：

```text
problem-analysis-workspace/viz_render.py
```

不要使用一个统一的万能样例解析器。不同题目的输入格式虽然都可能是数字和字符，但语义可能分别是数组、树边、网格、操作序列、DP 初值或查询区间，必须结合题意写专用解析逻辑。

## 使用场景

推荐按题型选择：

| 题型 | 推荐形式 | 说明 |
| --- | --- | --- |
| 图论 | Graphviz dot / Mermaid | 画样例图、DAG、拓扑关系、最短路局部过程 |
| 树 | `tree_draw.py` / Mermaid | 画样例树、递归关系、父子关系 |
| 二叉树 / 线段树 | `tree_draw.py` | 画二叉树、线段树区间结构、静态数据结构图 |
| DP / 背包 | Markdown 表格 | 展示状态定义、样例状态表、关键转移 |
| 网格 | Markdown 表格 | 展示起点、终点、障碍、可走区域 |
| 搜索 / 递归 | Mermaid / Graphviz dot | 展示搜索树或状态扩展 |
| 模拟 | Markdown 表格 | 展示样例过程中变量或数组的变化 |

普通题解建议最多 1 到 2 个可视化块，难题最多 3 个。图超过 30 个节点、DP 表超过 `10 x 10`、搜索树超过 3 层时，只展示关键局部。

## 写作要求

每个可视化块都必须有解释文字：

1. 图前说明“这张图展示什么”。
2. 图后用 2 到 5 句话说明“读者应该看什么”。
3. 表格必须解释行、列、单元格含义。
4. 不添加没有教学目的的图。

## Mermaid

题解页面已经加载 Mermaid。直接在 `index.md` 中使用：

````markdown
#### 状态转移图

这张图展示状态 `dp[i][j]` 的两个后继：

```mermaid
flowchart LR
  S0["dp[i][j]"] --> S1["不选：dp[i+1][j]"]
  S0 --> S2["选：dp[i+1][j+w]"]
```

从图中可以看到，每个物品都有“不选”和“选”两条路。
这就是 0/1 背包转移式的来源。
````

建议：

- Mermaid 节点 ID 使用 ASCII，例如 `S0`、`A1`。
- 中文写在 label 或正文说明里。
- 优先画样例或局部结构，不画过大的完整状态图。
- **宽度预算：一张图的自然宽度尽量控制在 1200px 以内**（约 6 个节点并排）。
  渲染层不再把宽图等比缩小，而是保持原始字号、由容器横向滚动接住（`problem-mermaid.js`
  的 `useMaxWidth: false` 与 `.mermaid svg { max-width: none }`）；图越宽，读者就越要左右拖。
- 并列节点太多时，按支线拆成几张小图，比一张大图好读。

## Graphviz

Markdown 渲染器会把 `dot` / `graphviz` 代码块识别成 Graphviz 内容。目前推荐两种用法：

1. 在题解里保留 dot 源码，方便维护。
2. 使用 `scripts/problem-tools/dot2png.py` 生成图片后插入题解。

dot 源码示例：

````markdown
#### 样例图

这张图把样例边画成无向图：

```dot
graph G {
  1 -- 2;
  2 -- 3;
  2 -- 4;
}
```

节点 `2` 是样例中的分叉点。
后面分析 DFS 时，可以重点观察从 `2` 出发的几条边。
````

生成图片：

```bash
python3 scripts/problem-tools/dot2png.py sample.dot sample.png
```

插入图片：

```markdown
![样例图](./sample.png)
```

如果需要把边列表转成 dot，可以使用：

```bash
python3 scripts/problem-tools/input2dot.py < sample.in > sample.dot
```

页面渲染时的尺寸规则：`dot` / `graphviz` 块按 Graphviz 的自然尺寸显示，只在
超出正文宽度时等比缩小，不会被放大填满正文。因此窄而高的默认布局不会再把页面
拉成几千像素长，但小图仍会显得细长；一条链、一个小三角这类图建议加
`graph [rankdir=LR]` 让它横向铺开。

## tree_draw.py

`tree_draw.py` 适合绘制树类数据结构，默认输出 SVG。它使用固定坐标布局，不依赖 Graphviz 的自动布局。

普通树：

```bash
tree_draw.py --type normal --input tree.txt --output tree.svg --markdown
```

二叉树：

```bash
tree_draw.py --type binary --input binary.txt --output binary.svg --markdown
```

线段树结构：

```bash
tree_draw.py --type segment --size 8 --output segment.svg --markdown --alt "线段树结构图"
```

在题目目录中配合 `ptool`：

```bash
ptool --cd problems/luogu/Pxxxx tree_draw --type binary --input tree.txt --output tree.svg --markdown
```

题解中插入：

```markdown
![二叉树示意图](./tree.svg)
```

详细说明见 [`docs/tools/tree_draw.md`](tools/tree_draw.md)。

## 题目专用可视化脚本

公共模板位于：

```text
scripts/problem-analysis-tools/viz_templates/
```

这些模板只提供小函数，例如数组表格、网格表格、DP 表格、Graphviz dot 和树 SVG。agent 应根据题意在 `problem-analysis-workspace/viz_render.py` 中组合使用它们。

推荐脚本行为：

- 默认从题目目录运行。
- 支持 `--help`。
- 默认读取 `in1` 或通过 `--input` 指定样例。
- 默认把最终素材输出到题目根目录。
- 不自动修改 `index.md`，只打印可粘贴的 Markdown 片段。

详细说明见 [`docs/tools/viz_templates.md`](tools/viz_templates.md)。

## Markdown 表格

DP、背包、网格和模拟题优先使用 Markdown 表格。

```markdown
#### DP 表格

这张表展示样例中前两层状态的变化：

| i \ j | 0 | 1 | 2 |
| --- | --- | --- | --- |
| 0 | 1 | 0 | 0 |
| 1 | 1 | 1 | 0 |

行表示已经处理到第 `i` 个元素。
列表示当前容量或状态值 `j`。
单元格中的值是 `dp[i][j]`。
```

表格不要太大。大表只展示关键行列，正文说明省略了哪些部分。

## DP 可视化

DP 可视化优先解释状态来源和更新过程，不只是展示最终表格。

推荐规则：

- 二维 DP、背包、网格 DP：用 Markdown 表格或 HTML 高亮表格展示关键局部。
- 一维 DP、LIS、前缀状态：用步骤表和小数组快照展示扫描过程。
- 状态依赖关系：可以用 Mermaid 表示抽象转移，不用 Mermaid 画完整 DP 表。
- 表超过 `10 x 10` 时，只展示关键行列或一次转移。

背包题需要先区分类型：

- 0/1 背包：重点展示 `j` 倒序更新，说明 `dp[j-w]` 仍是上一轮的值。
- 完全背包：重点展示 `j` 正序更新，说明 `dp[j-w]` 可以是本轮已更新的值。
- 多重背包：根据拆分或单调队列优化方式，只展示关键局部。
- 分组背包：展示同组候选物品如何竞争同一个 `dp[j]`。

LIS 需要区分两种可视化：

- `O(n^2)`：展示 `a[i]` 可以接在哪些前驱后面，以及 `dp[i]` 如何取最大。
- `O(n log n)`：展示 `lower_bound` 找到的位置，以及 `tails` 更新前后的变化。

如果题解使用滚动数组或一维优化，必须评估是否需要“压缩前后对照”，说明压缩后 `dp[j]` 在当前更新顺序下代表上一行还是当前行。

需要高亮来源格子时，可以输出 HTML 表格，并使用统一 class：

```text
dp-viz-table
dp-viz-current
dp-viz-source
dp-viz-changed
dp-viz-muted
dp-viz-choice
dp-viz-direction
```

可复用模板见 [`docs/tools/viz_templates.md`](tools/viz_templates.md) 中的 `dp_trace.py`。
