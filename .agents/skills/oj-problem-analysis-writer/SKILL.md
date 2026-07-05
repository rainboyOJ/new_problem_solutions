---
name: oj-problem-analysis-writer
description: >-
  Write Chinese OJ problem analysis content for this repository's ebook. Use
  this skill whenever the user asks to write a 题目解析, generate learning notes
  for an OJ problem, fill problems/<oj>/<problem_id>/index.md, turn
  problem-analysis-workspace/*.md into a final article, create a teaching
  brute.cpp, or use random data / 对拍 scripts while preparing a problem
  explanation. This skill writes analysis content, must complete brute.cpp,
  should strongly prefer a clear 01 序列 / 选择序列 recursive brute force when it
  naturally models the problem, and must follow oj-problem-format-spec for the
  final index.md.
---

# OJ 题目解析写作

这个 skill 专门负责写题目解析内容，让用户通过 Markdown 文档学会这道题，并最终生成符合 `oj-problem-format-spec` 的正式 `index.md`。

格式骨架由 `oj-problem-format-spec` 约束。本 skill 负责填充：

- 题意理解
- 关键观察
- 解法推导
- 正确性说明
- 边界情况
- 复杂度
- 实现对应关系

## 固定目录结构

只使用新结构，不兼容旧的扁平结构。

```text
problems/<oj>/<problem_id>/
  index.md
  main.cpp
  brute.cpp
  gen.py
  problem-analysis-workspace/
    01-problem-understanding.md
    02-observation-and-model.md
    03-solution-derivation.md
    04-correctness-and-edge-cases.md
    05-complexity-and-implementation.md
    06-final-index-draft.md
    07-ai-image-evaluation.md
    ai-image-plan.md
    ai-image-report.md
    duipai-report.md
```

Required for final article:

- `index.md`
- `main.cpp`
- `brute.cpp`

Optional but useful for verification:

- `gen.py`
- `problem-analysis-workspace/duipai-report.md`

## Required Companion Skill

Before writing final `index.md`, read:

```text
.agents/skills/oj-problem-format-spec/SKILL.md
```

Final `index.md` must follow that format:

- frontmatter at top
- frontmatter `tags` must be reviewed and updated for this problem
- frontmatter `description` must be a non-empty one-line summary of the core solution idea
- frontmatter `difficulty` must be reviewed and set to a standard difficulty enum; use `"未知"` only when uncertain
- frontmatter `recommend` must exist as an array; external recommendations are maintained by `oj-problem-relation-writer`
- `[[TOC]]`
- `### 题意`
- `### 思路`
- `### 代码`
- `### 复杂度`
- `### 总结`
- `@include-code(./main.cpp, cpp)`
- `@include-code(./brute.cpp, cpp)` in `### 思路`
- Mermaid、Graphviz、Markdown 表格等可视化内容必须遵守 `oj-problem-format-spec` 的“可视化辅助格式”。
- 如果题目需要样例、DP、树、图、网格或模拟过程可视化，使用 `oj-sample-visualizer` 生成题目专用 `problem-analysis-workspace/viz_render.py` 和素材；不要在本 skill 中临时发明通用可视化解析器。
- `index.md`、`main.cpp`、`brute.cpp` 和验证记录完成后，必须进行一次 AI 一图流后置评估；如果满足生成门槛，使用 `oj-ai-image-explainer`，否则在 `07-ai-image-evaluation.md` 记录不生成原因。
- 创建或修改 `main.cpp` / `brute.cpp` 时，必须使用 `oj-cpp-competitive-style`，保持 C++17 竞赛风格、中文注释和可读性。
- 创建 `brute.cpp` 时，优先尝试 01 序列 / 选择序列递归枚举；只有这种写法不自然、会误导学生，或比直接模拟/DP 更难理解时，才使用其它朴素写法。

## Source Priority

Use information in this order:

1. `problem-analysis-workspace/*.md`
2. `main.cpp`
3. `brute.cpp`
4. existing `index.md`
5. problem statement text or source URL provided by the user
6. `oj-problem-format-spec`

If workspace files already exist, read them first and preserve useful user-written content. Do not overwrite process notes blindly.

## Process Documents

If `problem-analysis-workspace/` or its stage files do not exist, create them and fill them progressively.

## Required `brute.cpp`

This skill must finish a teaching brute-force solution before the final `index.md` is considered complete.

Path:

```text
problems/<oj>/<problem_id>/brute.cpp
```

Purpose:

- help the reader understand the problem through the most direct correct idea;
- provide a trusted small-data solution for 对拍;
- make the bottleneck of the naive method explicit before deriving `main.cpp`.

Rules:

- If `brute.cpp` already exists, read it and improve it if needed.
- If `brute.cpp` does not exist, create it.
- It must be a complete C++17 program with the same input/output format as `main.cpp`.
- It must follow `oj-cpp-competitive-style`.
- Prefer 01 序列 / 选择序列递归枚举 when it naturally models the problem; otherwise use direct enumeration, simulation, small-data DP, or another clearly correct small-data method.
- Use straightforward variable names and a few useful Chinese comments when they help understanding.
- High complexity is acceptable, but it must be described as small-data/verification code.
- If the brute-force correctness is uncertain, record the uncertainty in `04-correctness-and-edge-cases.md` and do not claim reliable 对拍.
- Do not deliver a final `index.md` without a completed `brute.cpp`, unless the user explicitly pauses or changes this requirement.

### 01 序列 / 选择序列暴力优先

When writing a new `brute.cpp`, first ask whether the problem can be explained as a sequence of simple decisions. Prefer this style if the answer is yes.

Natural cases include:

- each element is selected or not selected;
- each position chooses one digit, value, direction, edge, operation, or next state;
- a path/search process chooses one legal next move at each layer;
- a left-to-right process decides whether to skip the current position or start/use a structure here.

Use ordinary recursive DFS as the default shape. The goal is to make the enumeration object obvious to a student:

```text
处理到第 i 个位置
选择 0：不选 / 不做 / 跳过
选择 1：选 / 做 / 使用当前对象
递归处理下一层
```

This is a strong preference, not an absolute rule. Do not force 01 序列 / 选择序列 when the resulting code is less clear than a direct simulation, formula check, BFS, or small-data DP. For example, deterministic simulation problems and pure arithmetic problems usually should keep a direct brute-force or simulation style.

For multi-branch choices, still use the same teaching idea: "each recursion layer handles one decision point, then enumerates all legal choices at this point." This covers problems where the branch count is not exactly 2, such as choosing one digit from 0..9, choosing one adjacent vertex, choosing one interval, or choosing one operation.

If repeated states make the recursive brute force too slow even on small random tests, keep the recursive choice structure and add simple `memo` / `vis` arrays or maps. This is acceptable because it helps students see the bridge from brute force to DP. Do not turn `brute.cpp` into a highly optimized solution disguised as a brute force.

When this style is used, the file header should state it clearly, for example:

```cpp
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// brute.cpp：小数据暴力解，把每一步操作看成选择序列来递归枚举。
```

### Existing Articles And `brute_01_style.cpp`

For new problem explanations, make `brute.cpp` itself use the clearest suitable brute-force style. Do not create `brute_01_style.cpp` by default.

For existing articles, if `brute.cpp` is already stable for 对拍 or the current text is already built around it, do not rewrite it only to change style. In that case, it is acceptable to add an optional second file:

```text
problems/<oj>/<problem_id>/brute_01_style.cpp
```

Reference it in `index.md` after the existing `@include-code(./brute.cpp, cpp)` using a folded block:

```markdown
下面是另一种「01 序列」风格的暴力写法。它把每一步决策看成选择序列，更适合训练递归枚举思维：

<details>
<summary>另一种暴力写法：01 序列</summary>

@include-code(./brute_01_style.cpp, cpp)

</details>
```

`brute_01_style.cpp` is optional teaching material. It is not a required file for new explanations and should not replace `brute.cpp` as the default 对拍 baseline unless explicitly chosen.

### `01-problem-understanding.md`

Purpose: make the problem statement precise.

Required sections:

```markdown
# 题意理解

## 输入与输出

## 要求求什么

## 约束条件

## 等价表述
```

### `02-observation-and-model.md`

Purpose: identify the key observation and algorithm model.

Required sections:

```markdown
# 关键观察与模型

## 直接想法

## 关键性质

## 可用模型

## 为什么这个模型适用
```

Also evaluate whether the problem needs visualization. Record:

```markdown
## 可视化评估

- 是否需要可视化辅助：是 / 否
- 推荐形式：Markdown 表格 / Mermaid / Graphviz / 图片 / 不需要
- 解释对象：样例 / 状态 / 转移 / 图结构 / 搜索树 / 贪心选择 / 不需要
- 如果不需要，原因：
```

Trigger rules:

- 图论题：必须考虑 Graphviz 或 Mermaid 样例图。
- 树题、二叉树、线段树题：必须考虑用 `tree_draw.py` 生成 SVG 树图。
- DP 题：必须考虑 Markdown 表格，背包题尤其优先表格。
- 网格题：必须考虑二维表格。
- 搜索、递归题：必须考虑搜索树或状态转移图。
- 模拟题：如果样例过程复杂，必须考虑过程表格。

If visualization is useful, invoke the `oj-sample-visualizer` skill. The visualizer should create a problem-specific script:

```text
problem-analysis-workspace/viz_render.py
```

The final article should only include the generated teaching artifact and explanation text, not the whole visualization script.

### `03-solution-derivation.md`

Purpose: teach the solution by layer, not by jumping to the final answer.

Required sections:

```markdown
# 解法推导

## 朴素想法

## 瓶颈分析

## 优化思路

## 最终做法

## 与代码实现的对应关系
```

This file should explain how `brute.cpp` represents the naive idea, why it is too slow for full constraints, and which bottleneck motivates `main.cpp`.

If `brute.cpp` uses 01 序列 / 选择序列 recursion, explain:

- what one recursion layer represents;
- what choices are made at that layer;
- why the recursion enumerates all possibilities for small data;
- where the bottleneck is;
- how the optimized `main.cpp` avoids that bottleneck.

### `04-correctness-and-edge-cases.md`

Purpose: explain why the solution is correct and what edge cases matter.

Required sections:

```markdown
# 正确性与边界情况

## 正确性说明

## 可能的反例检查

## 边界情况

## 对拍或手工验证记录
```

This file should state whether `brute.cpp` is reliable enough for 对拍. If 对拍 was not run, record why.

### `05-complexity-and-implementation.md`

Purpose: connect the final method to implementation details.

Required sections:

```markdown
# 复杂度与实现

## 时间复杂度

## 空间复杂度

## 关键变量

## 核心循环

## 边界处理

## 与 main.cpp 的对应关系
```

Do not write line-by-line code commentary. Explain only the key implementation correspondence.

Also mention how the optimized implementation differs from `brute.cpp`.

### `06-final-index-draft.md`

Purpose: draft the final article before updating `index.md`.

It should already follow the final article structure:

```markdown
---
oj: ""
problem_id: ""
title: ""
description: ""
difficulty: "未知"
date: YYYY-MM-DD HH:mm
toc: true
tags: ["算法标签", "数据结构标签"]
categories: []
source:
---

[[TOC]]

### 题意

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

### 总结
```

Do not leave `tags: []` in the draft unless the problem is genuinely impossible to classify from available materials. Choose concise Chinese tags that help users search and review problems later, such as algorithm family, data structure, implementation technique, or difficulty-relevant pattern.

Do not leave `description: ""` in the draft. The description must summarize the core solution idea in one line, usually 20 to 80 Chinese characters and at most 120 characters. It should describe the algorithmic insight, not the statement background. Avoid empty phrases such as “本题主要考察”, “经典题”, “详见下文”, or “看代码”.

Do not leave `difficulty` unreviewed. Use the standard enum from `oj-problem-format-spec`; if the difficulty cannot be inferred from the statement, code, or known OJ rating, keep `"未知"` explicitly.

## Final Article Style

The final `index.md` should be concise but still teach the idea.

In `### 思路`, keep a compressed layered progression:

1. briefly state why the naive idea is not enough;
2. include `@include-code(./brute.cpp, cpp)` as the teaching brute-force solution;
3. state the bottleneck of `brute.cpp`;
4. state the key observation;
5. explain the final method;
6. mention the important implementation correspondence.

If `brute.cpp` uses 01 序列 / 选择序列 recursion, add 1 to 3 sentences after the include to explain the enumeration object. Good forms:

```markdown
这个暴力把问题看成一串选择：处理到第 `i` 个位置时，要么不选它，要么选它。
这种写法只适合小数据，但能直接看出“枚举了哪些可能性”。
```

```markdown
这个暴力把每一步操作看成选择序列：当前状态下枚举所有合法下一步，再递归处理后续状态。
```

Also include visualization when it improves learning:

- Use Markdown tables for DP states, knapsack tables, grids, and step-by-step sample traces.
- Use Mermaid for flowcharts, state transitions, simple trees, and process diagrams.
- Use Graphviz dot for graph theory samples, trees, DAGs, and topology-like structures.
- Use `tree_draw.py` for ordinary trees, binary trees, segment trees, and static tree-shaped data structures.
- Use generated images only when source-style diagrams are too large or need hand annotations.

Visualization is not mandatory for every problem, but it is a mandatory evaluation item. If the problem is graph/tree/DP/grid/search/simulation-heavy, prefer including one small visual block unless it would be redundant.

AI-generated one-page images are a separate post-processing step, not part of the early sample visualization workflow. After the final `index.md` is written from `06-final-index-draft.md` and checked against `main.cpp` / `brute.cpp`, evaluate whether the completed article needs a global "一图流解析":

- Use `oj-ai-image-explainer` only when the final article has a modeling jump, multi-stage DP/graph/tree/binary-search/greedy reasoning, or a long enough route that a 3 to 5 panel overview would help students.
- Do not use AI images for exact DP values, edge weights, sample traces, or code. Those belong to `oj-sample-visualizer`, Mermaid, Graphviz, SVG, or Markdown tables.
- If no image is needed, create or update `problem-analysis-workspace/07-ai-image-evaluation.md` with the reason and stop.
- If an image is generated and passes review, only make a minimal final patch to `index.md`: append `### 一图流解析` after `### 总结`, add 1 to 3 explanatory sentences, and insert `![一图流解析](./one-page-explainer.png)`.
- Treat the dense AI board as a read-after review aid. Do not place it at the beginning of `### 思路` unless the user explicitly asks for a read-before overview.
- Do not rewrite the main article while inserting the AI image. Treat it as a final reference patch.

Every visual block in final `index.md` must:

- state what it shows before the figure/table;
- explain what to observe after the figure/table in 2 to 5 sentences;
- keep the displayed data small and tied to the sample or one key local structure;
- avoid decorative diagrams.

When using `tree_draw.py`, prefer SVG output in the current problem directory or a local `assets/` directory:

```bash
ptool --cd problems/<oj>/<problem_id> tree_draw --type binary --input tree.txt --output tree.svg --markdown
ptool --cd problems/<oj>/<problem_id> tree_draw --type segment --size 8 --output segment-tree.svg --markdown
```

Then reference it from `index.md`:

```markdown
![二叉树示意图](./tree.svg)
```

Do not turn `index.md` into a raw dump of all process notes. The detailed learning path belongs in `problem-analysis-workspace/*.md`.

The `### 代码` section still contains only the final accepted/optimized solution:

```markdown
@include-code(./main.cpp, cpp)
```

## Consistency Check

Before updating `index.md`, check consistency with `main.cpp` when it exists:

- The frontmatter `tags` are updated from the solved content, not left as a stale placeholder.
- The frontmatter `description` is non-empty, one line, and matches the final solution.
- The frontmatter `recommend` exists as an array, normally `recommend: []` unless verified external practice recommendations are available.
- Before choosing tags, query the repository's existing tag set and prefer accurate existing tags over inventing new variants:

```bash
python3 scripts/problem-analysis-tools/list_tags.py
python3 scripts/problem-analysis-tools/list_tags.py --format plain
```

- Tags should describe the final solution and important prerequisite ideas, for example `模拟`, `枚举`, `动态规划`, `贪心`, `图论`, `树形结构`, `最短路`, `二分`, `前缀和`, `数学`, `组合计数`, `高精度`, `字符串`, `数据结构`.
- If an existing tag is accurate, reuse it exactly. Only introduce a new tag when the current tag set has no precise fit.
- If the existing `index.md` already has useful tags, preserve them when still accurate and add missing tags.
- The algorithm description roughly matches the implementation.
- The complexity can be explained from the code structure.
- The code section uses `@include-code(./main.cpp, cpp)`.
- The `### 思路` section uses `@include-code(./brute.cpp, cpp)`.
- `brute.cpp` is complete and matches the same input/output format.
- If `brute.cpp` naturally could be 01 序列 / 选择序列 but is not, the process notes or article should make the chosen brute-force style reasonable.
- If an optional `brute_01_style.cpp` is added for an existing article, it appears after the original `brute.cpp` include in a folded `<details>` block and is not presented as the formal solution.
- Key implementation details mentioned in the article exist in the code.
- Visualization was evaluated in `02-observation-and-model.md`.
- AI 一图流 was evaluated after the final article in `07-ai-image-evaluation.md`; if an image was inserted, `ai-image-report.md` records that it passed review.
- Any Mermaid / Graphviz / table used in `index.md` has nearby explanatory text and follows the format spec.
- After finishing the article, evaluate whether `pre` / `common` / `recommend` should be maintained by `oj-problem-relation-writer`; do not invent external OJ links from memory.
- If no verification was run, say so in the process notes; do not imply proof by testing.

## Verification Scripts

Use scripts from:

```text
scripts/problem-analysis-tools/
```

Available tools:

- `list_tags.py`: list existing tags in all problem explanations; use it before writing frontmatter tags.
- `gen_random.py`: generic random data generator for arrays, trees, graphs, strings, and permutations.
- `duipai.py`: non-interactive stress testing script for agents and automation.
- `duipai-human.py`: interactive wrapper for humans; it calls `duipai.py`.

Default per-problem verification files:

```text
problems/<oj>/<problem_id>/
  main.cpp
  brute.cpp
  gen.py
```

`brute.cpp` is required. `gen.py` is not strictly required for the final article, but create or complete it when the input format is clear and random small data can be generated reasonably.

When `brute.cpp` uses 01 序列 / 选择序列 brute force, tune `gen.py` for that brute-force scale instead of full constraints. Examples:

- subset recursion: usually keep `n <= 15`;
- permutation recursion: usually keep `n <= 8`;
- path/search recursion: limit node count, edge count, and maximum steps;
- digit/value choice recursion: limit length, target value, or state count;
- interval/state recursion: limit `n` and the reachable state space.

The point of random testing is to compare a trusted small-data brute force with `main.cpp`. If 对拍 times out because the generator created full-size data, the generator is wrong for this verification role.

Recommended command:

```bash
python3 scripts/problem-analysis-tools/duipai.py \
  --gen problems/<oj>/<problem_id>/gen.py \
  --user problems/<oj>/<problem_id>/main.cpp \
  --brute problems/<oj>/<problem_id>/brute.cpp \
  -n 200
```

Only run 对拍 when `gen.py`, `main.cpp`, and `brute.cpp` exist and are runnable, or when the user asks for it. If 对拍 is not possible, record that it was not run and why.

## Safety Rules

- Do not invent problem title, source URL, or constraints.
- Do not claim a solution is accepted unless there is evidence.
- Do not claim 对拍 was run unless the script actually ran.
- Do not overwrite user-written process notes without preserving useful content.
- Do not write full code into `index.md`; use `@include-code(./brute.cpp, cpp)` in `### 思路` and `@include-code(./main.cpp, cpp)` in `### 代码`.
- Do not claim `brute.cpp` is trusted unless its correctness is clear enough for small data.
- Do not finish final `index.md` with `tags: []` or irrelevant inherited tags when enough information exists to classify the problem.
- Do not finish final `index.md` without reviewing `difficulty`. Use one of: `入门`, `普及-`, `普及/提高-`, `普及+/提高`, `提高+/省选-`, `省选/NOI-`, `NOI/NOI+/CTSC`, `未知`.

## Final Response

After editing, report briefly:

- which problem directory was updated;
- which process Markdown files were created or updated;
- whether `brute.cpp` was created or updated;
- whether `index.md` was written from `06-final-index-draft.md`;
- which `tags` were written into `index.md` frontmatter;
- which `description` was written into `index.md` frontmatter;
- whether `pre` / `common` / `recommend` were evaluated or left for `oj-problem-relation-writer`;
- whether visualization was evaluated and what was used, if anything;
- whether 对拍 was run and where the report is;
- any missing fields, code files, or verification material.
