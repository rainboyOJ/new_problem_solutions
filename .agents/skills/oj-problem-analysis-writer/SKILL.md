---
name: oj-problem-analysis-writer
description: >-
  Write Chinese OJ problem analysis content for this repository's ebook. Use
  this skill whenever the user asks to write a 题目解析, fill
  problems/<oj>/<problem_id>/index.md, turn problem-analysis-workspace notes
  into an article, create a teaching brute.cpp, or use random data / 对拍 while
  preparing an explanation. It selects a layout from the actual solution
  relationships, supports direct, brute-to-final, parallel, and progressive
  articles, and follows oj-problem-format-spec for the final Markdown.
---

# OJ 题目解析写作

目标是让读者理解题目的形式化模型、关键观察、解法推导、正确性、边界、复杂度和实现对应关系，并产出可渲染的 `index.md`。本 skill 负责算法正文和写作流程；格式、frontmatter 和 Markdown 扩展分别以 `oj-problem-format-spec`、`rbook-markdown` 为准，C++ 风格以 `oj-cpp-competitive-style` 为准，关系元数据以 `oj-problem-relation-writer` 为准。

## 开始顺序

1. 确认 `problems/<oj>/<problem_id>/`。若目录或 `index.md` 不存在，执行 `python3 scripts/problem-analysis-tools/new-problem.py <problem URL>`；已有目录不重建、不覆盖。
2. 读取 `problem.md`、现有 `index.md`、全部约束和子任务、所有解法文件（`main.*`、`brute.cpp` 及额外代码）以及 `problem-analysis-workspace/*.md`。已有过程文档优先保留，不盲目覆盖。
3. 读取 `oj-problem-format-spec/SKILL.md` 和格式 reference；需要时按下表加载专项 reference。不要把新脚本或固定模板当成解法依据。
4. 先判断解法关系，再在 `02-observation-and-model.md` 记录布局、依据、层次、代码对应关系和正式主解；随后只重写 `index.md` 的正文骨架，保留有效 frontmatter 和用户正文。
5. 逐层填写过程文档，形成 `06-final-index-draft.md`，再把草稿写入 `index.md`。最终检查代码引用、frontmatter、公式、图示和验证记录。

## 布局判定

根据已核实的约束、子任务和代码之间的关系选择，优先级如下：

1. **子任务递进型**：真实约束形成层层推进，每层复用观察并移除新的瓶颈。
2. **并列多解法型**：至少两个独立完整解法，是替代关系而非连续优化。
3. **暴力到正解型**：朴素解能清楚暴露最终解法消除的瓶颈。
4. **直接正解型**：没有值得单独教学的解法层。

不要按“简单/困难”或未经核实的“60 分/80 分”选布局。递进标题使用真实约束，如 `## 子任务解法：$k \leqslant 4$`。在 `02-observation-and-model.md` 至少记录：

```markdown
## 文章结构判定

- 选定布局：直接正解型 / 暴力到正解型 / 并列多解法型 / 子任务递进型
- 判定依据：
- 解法层次：
- 各代码文件对应关系：
- 正式主解：
```

最终正文必须有 `[[TOC]]`、`## 形式化题目`、所选布局和 `## 总结`；每个正式解法拥有自己的 `### 思路`、`### 代码`、`### 复杂度`（递进层可用 `### 复杂度与瓶颈`）。正式主解在对应代码小节使用 `@include-code(./main.<ext>, <lang>)`。完整布局骨架见 [`oj-problem-format-spec/references/layouts.md`](../oj-problem-format-spec/references/layouts.md)。

## 场景路由

只读取当前任务需要的专项资料：

| 场景 | 读取 | 关键产物 |
| --- | --- | --- |
| 所有题解 | [`process-documents.md`](references/process-documents.md) | 过程文档与最终草稿 |
| 需要正式暴力层或 `brute.cpp` | [`brute-force.md`](references/brute-force.md) | 小数据基线、瓶颈说明 |
| 对拍、样例、USACO 官方数据 | [`verification.md`](references/verification.md) | 验证记录和报告 |
| DP、图、树、网格、搜索、复杂模拟图示 | [`visualization.md`](references/visualization.md) | `viz_render.py`、图表或 `final-visualization.md` |
| 用户目标是 Haskell/Rust/Python 等语言或语法学习 | [`language-learning.md`](references/language-learning.md) | 语言教学文章，不强制暴力 |

格式细节必须读取 `../oj-problem-format-spec/references/frontmatter.md` 和 `layouts.md`；用户明确要求修正旧文章时，额外读取 `migration.md`。旧文章默认不迁移、不批量改写，旧文内容审查交给 `oj-problem-analysis-reviewer`。

## 过程文档与正文要求

`problem-analysis-workspace/` 不存在时创建；核心信息必须记录题意、关键观察/模型、布局判定、解法推导、正确性和边界、复杂度及实现对应关系。复杂题可拆分为专项文件，简单直解题可合并记录；`duipai-report.md`、`final-visualization.md` 和 `viz_render.py` 只在实际使用时生成。具体章节和草稿约束见 `process-documents.md`。

`## 形式化题目` 去除故事背景，只保留数学结构。正文简洁但要解释“为什么这样想到”，不能把过程文档原样倾倒进文章，也不能在 Markdown 中粘贴完整代码。

## 完成标准

- frontmatter 的 `description`、`difficulty`、`tags` 已根据题目和代码复核；关系字段只评估是否需要交给 `oj-problem-relation-writer`，不凭记忆编造外部链接。
- 直接解法或明确语言学习文章可以跳过正式 `brute.cpp`，但必须在过程文档解释重复性和验证方式；其他算法文章通常需要完整、同输入输出格式的 `brute.cpp`。
- DP 正文在对应思路中有小规模 DP/状态转移表；其他非平凡图示按 `visualization.md` 评估。
- 正确性、边界、复杂度和代码实现互相一致；未运行对拍或样例时如实记录，不声称通过。
- 运行适用的仓库检查/测试，确认主解文件存在、引用路径正确、无可见占位文本和虚构题面信息。

## 安全与交付

不编造题目标题、来源、约束、接受状态、测试结果或关系；不覆盖用户过程笔记，不把 `brute.cpp` 伪装成正解，不为语言学习或纯直解题强行制造暴力层。完成后简短报告目录、过程文档、代码文件、草稿是否写回、frontmatter 标签/摘要、关系评估、可视化和对拍情况，以及仍缺失的材料。
