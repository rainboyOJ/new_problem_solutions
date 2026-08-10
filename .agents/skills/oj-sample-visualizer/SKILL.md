---
name: oj-sample-visualizer
description: Create problem-specific sample and solution-route visualizations for OJ problem explanations. Use this skill when the user asks to visualize examples, DP tables, grids, trees, graphs, state transitions, simulation processes, a final 图示解析, or to generate problem-analysis-workspace/viz_render.py for a problem. This skill creates teaching visuals and helper scripts, but does not write the full problem analysis article.
---

# OJ 样例与思路可视化生成

这个 skill 负责为单道 OJ 题目生成“题目专用”的样例与思路可视化脚本和素材，帮助读者理解题意、样例、状态转移、数据结构和完整解法路线。

核心原则：不要写万能样例解析器。不同题目的输入语义不同，必须结合题意生成当前题目的专用脚本。

## 边界

本 skill 负责：

- 判断题目是否需要可视化辅助。
- 根据题意、样例和输入格式设计可视化方式。
- 在当前题目目录生成或修改 `problem-analysis-workspace/viz_render.py`。
- 生成 ASCII 文本图、Markdown 表格、Mermaid、Graphviz dot、SVG 等可插入题解的素材。
- 对非平凡算法题起草最终 `## 图示解析` 的紧凑思路图与配套说明。
- 必要时复用 `scripts/problem-analysis-tools/viz_templates/` 和 `tree_draw.py`。

本 skill 不负责：

- 写完整 `index.md` 题解正文。
- 判断最终 Markdown 章节格式。
- 维护 `pre` / `common` / `recommend` 关系。
- 为所有题目提供一个通用自动识别 CLI。

完整题解正文由 `oj-problem-analysis-writer` 负责。最终格式由 `oj-problem-format-spec` 负责。

## 固定输出位置

题目专用脚本写入：

```text
problems/<oj>/<problem_id>/problem-analysis-workspace/viz_render.py
```

生成的可提交可视化素材优先放在题目目录：

```text
problems/<oj>/<problem_id>/
  sample-grid.md
  sample-graph.dot
  sample-tree.svg
  dp-table.md
  final-visualization.md
```

过程输入、草稿和中间文件放在 `problem-analysis-workspace/`。最终要在 `index.md` 中引用的 SVG、图片或 Markdown 片段，才放到题目根目录。

## 工作流程

1. 读取题目目录中的 `index.md`、`problem.md`、样例文件、`main.cpp`、`brute.cpp` 和已有 `problem-analysis-workspace/*.md`。
2. 判断可视化目标：
   - 解释样例输入结构；
   - 解释样例推演过程；
   - 解释 DP 表或状态转移；
   - 解释图、树、网格、搜索树或数据结构。
   - 在读完正文后复盘从建模到答案的核心路线。
3. 选择最小可视化形式：
   - 数组、DP、网格、模拟过程：Markdown 表格；
   - 树、二叉树、线段树：SVG，优先复用 `tree_draw.py` 或其 Python 模块；
   - 普通图、DAG、拓扑关系：Graphviz dot 或 Mermaid；
   - 状态转移、流程、搜索树：Mermaid 或 dot；
   - 小型流程、递归分支、简短状态变化：ASCII 文本图；
   - 复杂静态结构：SVG。
4. 创建 `problem-analysis-workspace/viz_render.py`。脚本必须适配当前题目的输入语义，允许硬编码样例中的含义说明。
5. 运行脚本生成素材。
6. 输出可粘贴到 `index.md` 的 Markdown 片段，并说明图前图后应写什么。

## 最终图示解析

对于有明确建模或多步骤推导的算法题，额外给出一份最终思路图示，供 `oj-problem-analysis-writer` 放在文章末尾的 `## 图示解析`。

默认使用 ASCII 文本图。它应只保留从“输入/建模”到“关键观察”再到“算法/答案”的主线：

- 节点不超过 12 个；
- 递归、分支或流程深度不超过 4 层；
- 不展示样例的精确数值、完整 DP 表或代码细节；
- 使用真正的 ASCII 分支符号，例如 `|-` 和 `` `-``。

出现跨边、多个汇合点或需要横向比较的状态时，改用 Mermaid。真实图论样例仍优先用 Graphviz；DP 转移细节仍优先用表格。不要把局部样例图硬拼成总览，也不要生成位图或海报式一图流。

将最终图示与说明写入题目目录的 `final-visualization.md`。文件应只包含可直接移入 `index.md` 的内容：

````markdown
## 图示解析

这张图串起本题从建模到得到答案的主线：

```text
输入对象
`- 关键观察
   `- 选择算法
      `- 得到答案
````

先看每个节点代表的推理结论，再顺着分支检查它如何导向下一步。
图中只保留正文已经证明过的关键关系，不替代正文中的样例推演和正确性说明。
```

直接输入输出、极短模拟、纯语法学习文章可以不创建该文件。此时在 `02-observation-and-model.md` 说明图示不会带来额外理解即可。

## `viz_render.py` 要求

- 使用 Python 3。
- 顶部写明“这个脚本是当前题目专用可视化脚本”。
- 默认从当前题目目录运行。
- 支持 `--help`。
- 支持 `--sample` 或 `--input` 指定样例文件；如果题目样例很特殊，可以默认读取 `in1`。
- 支持 `--out-dir` 指定输出目录，默认输出到题目根目录。
- 不用 `subprocess` 调用本仓库 Python 工具；需要复用时使用 `import`。
- 不自动修改 `index.md`，只输出可粘贴片段。
- 脚本逻辑要尽量短，复杂解析写成小函数。
- 对题目语义做中文注释，帮助用户以后手工修改。

推荐骨架：

```python
#!/usr/bin/env python3
"""当前题目专用的样例可视化脚本。"""

from __future__ import annotations

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="生成当前题目的样例可视化素材。")
    parser.add_argument("--input", default="in1", help="样例输入文件，默认 in1。")
    parser.add_argument("--out-dir", default=".", help="输出目录，默认题目根目录。")
    args = parser.parse_args()

    problem_dir = Path.cwd()
    out_dir = (problem_dir / args.out_dir).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    text = (problem_dir / args.input).read_text(encoding="utf-8")
    # TODO: 按当前题目的输入语义解析 text。
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
```

## 可复用模板

公共模板放在：

```text
scripts/problem-analysis-tools/viz_templates/
```

模板只提供可复制或可 import 的基础函数，不提供万能入口。

优先使用：

- `array_table.py`：一维数组转 Markdown 表格。
- `grid_table.py`：二维网格转 Markdown 表格。
- `dp_table.py`：DP 表格模板或数值表。
- `dp_trace.py`：经典 DP 的小规模教学追踪器和高亮表格渲染。
- `graph_dot.py`：边列表转 Graphviz dot。
- `tree_svg.py`：复用 `tree_draw` 生成 SVG。

如果某个题目的 `viz_render.py` 中出现了可以复用的稳定函数，再沉淀回 `viz_templates/`。

## DP 可视化规则

DP 可视化的核心是“状态来源和更新过程”，不是单纯展示最终表格。

### 输出形式

- 二维 DP、背包、网格 DP：以 Markdown 表格或 HTML 高亮表格为主。
- 一维 DP、LIS、前缀状态：以步骤表和小数组快照为主。
- 状态依赖关系：可以用 Mermaid 展示抽象依赖，不用 Mermaid 画大 DP 表。
- 需要高亮当前格、来源格、更新格时，输出 HTML `<table>`。

默认输出 Markdown 表格；只有需要突出来源或更新方向时才输出 HTML 表格。

### HTML class 约定

生成 HTML 表格时使用稳定 class，方便前端统一样式：

```text
dp-viz-table
dp-viz-current
dp-viz-source
dp-viz-changed
dp-viz-muted
dp-viz-choice
dp-viz-direction
```

含义：

- `dp-viz-current`：当前正在计算的状态。
- `dp-viz-source`：转移来源状态。
- `dp-viz-changed`：本轮被更新的位置。
- `dp-viz-muted`：和当前讲解无关的格子。
- `dp-viz-choice`：多个候选转移中的最终选择。
- `dp-viz-direction`：一维 DP 的遍历方向说明。

### 二维 DP

默认只展示关键局部：

- DP 表不超过 `10 x 10` 时，可以展示完整表。
- DP 表超过 `10 x 10` 时，只展示关键行、关键列、目标格子附近，或一次具体转移。
- 表格必须说明行、列、单元格分别表示什么。
- 如果展示某一格 `dp[i][j]`，必须说明它来自哪些状态。

常见模型：

- 背包：优先展示某个物品 `i` 的上一行和当前行，而不是完整 `n x W` 表。
- 网格 DP：优先展示样例网格和关键格子的来源方向。
- 区间 DP：优先展示长度 `len` 的推进顺序，以及一个区间 `dp[l][r]` 的切分来源。

### 背包

生成背包可视化前必须先判断类型。

- 0/1 背包：强调 `j` 倒序更新；说明 `dp[j-w]` 仍然是上一轮值。
- 完全背包：强调 `j` 正序更新；说明 `dp[j-w]` 可以是本轮已更新值。
- 多重背包：若用二进制拆分，展示拆分包；若用单调队列优化，展示同余类队列，不画完整大表。
- 分组背包：强调每组最多选一个，展示同一组候选物品如何竞争更新同一个 `dp[j]`。

如果题解使用滚动数组或一维优化，必须评估是否需要“压缩前后对照”：

- 先说明二维定义中 `dp[i][j]` 的来源。
- 再说明压缩后 `dp[j]` 在当前更新顺序下代表上一行还是当前行。
- 用步骤表展示更新方向，例如 `j: W -> w` 或 `j: w -> W`。

### 一维 DP 与 LIS

一维 DP 关注扫描顺序和数组快照。

LIS 必须区分两种讲法：

- `O(n^2)`：生成扫描步骤表，包含 `i`、`a[i]`、可接前驱、`dp[i]`、当前答案。
- `O(n log n)`：生成 `tails` 更新表，包含 `i`、`a[i]`、`lower_bound` 位置、更新前 `tails`、更新后 `tails`、当前答案。
- 如果两种解法都讲，先用 `O(n^2)` 表帮助理解状态定义，再用 `tails` 表解释优化。

### 可视化计算逻辑

DP 可视化脚本可以自己实现一份小规模、教学版 DP 计算逻辑。

要求：

- 只面向样例或小数据。
- 状态定义必须和题解一致。
- 保留关键中间状态。
- 用中文注释解释状态含义。
- 不作为提交代码，不要求最优复杂度。

不要依赖 `main.cpp` 的优化实现还原中间过程。`brute.cpp` 可用于理解答案，但不一定能输出 DP 状态。

### Insertion note

DP 可视化脚本必须输出可粘贴说明草稿，但不直接修改 `index.md`。

局部 DP 可视化的说明草稿包括：

- 推荐插入章节：`## 思路`。
- 推荐三级标题。
- 图前 1 句话。
- 图后 2 到 5 句话。
- 生成文件路径。

## 写入题解的要求

生成素材后，给 `oj-problem-analysis-writer` 的插入建议必须包含：

- 放在 `## 思路`。
- 四级标题，例如 `#### 样例图`、`#### DP 表格`。
- 图前 1 句话：这张图或表展示什么。
- 图后 2 到 5 句话：读者应该观察什么。
- 本地 SVG 使用 `![说明](./xxx.svg)`。
- Mermaid / dot 使用 fenced code block。
- ASCII 文本图使用 `text` fenced code block，并配套图前图后说明。
- 若生成 `final-visualization.md`，说明它应作为 `## 图示解析` 放在 `## 总结` 后。

不要为了装饰加图。普通题解最多 1 到 2 个可视化块，难题最多 3 个。

## 选择规则

- 如果样例本身一眼能看懂，不强行生成图。
- 如果图会超过 30 个节点，只画关键局部。
- 如果 DP 表超过 `10 x 10`，只展示关键行列。
- 如果输入有多组测试，只挑最能说明问题的一组。
- 如果题目输入需要复杂语义解释，宁可在 `viz_render.py` 中写题目专用解析，也不要扩展通用模板参数。
- 如果可视化结论不确定，把不确定性写入 `problem-analysis-workspace/`，不要写进最终题解。
