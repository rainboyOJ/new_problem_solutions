---
name: oj-problem-analysis-writer
description: >-
  将已核验的 OJ 解法、代码和过程笔记写成或修订为本仓库的中文题解 index.md。
  用于题解正文写作、文章补全、分层或并列解法的讲解组织。
  从题目到代码、验证和文章的完整任务由 oj-problem-workflow 编排；
  本 skill 只负责写作阶段的材料核对、布局、草稿和正文，不另起整题流程。
---

# OJ 题目解析写作

将可核验的算法材料组织成读者能够理解的正式正文。完整任务的阶段协调由 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md) 负责；算法探索由 [`oj-solution-planner`](../oj-solution-planner/SKILL.md) 负责；格式与 Markdown 分别以 `oj-problem-format-spec`、`rbook-markdown` 为准。

## 入口与范围

- 已由 workflow 进入写作阶段时，只消费交接材料并执行本 skill；发现缺口返回当前协调阶段，不重新启动 workflow。
- 用户直接点名本 skill 且要求从题目到代码、验证和文章的完整任务时，一次性交接给 workflow。它后续再次进入本 skill 时只执行写作，不形成循环。
- 用户只要求按现有材料写正文或局部修订时，保持该范围；可以核对必要算法事实，不能自动扩展为多份代码、全题迁移或整套测试。

## 写作顺序

1. 确认目标目录与用户要求的正文范围，读取题面、已有 `index.md`、实际源码和过程记录。缺失题面或目录等前置材料时交回 workflow 的材料阶段；只写文章的任务先查已有来源，不盲目重建或覆盖。
2. 核对 `01` 至 `05` 的算法描述、证明、复杂度、实现与验证状态，使用 planner 的交接约定解释状态。已可靠的材料直接复用；事实不足时列出具体缺口，不把猜想写成结论。
3. 读取 `oj-problem-format-spec/SKILL.md` 及需要的 references，根据已核验的解法关系确认布局，在 `02` 的 `文章结构判定` 中记录选定布局与教学取舍。
4. 组织思路、证明、边界、复杂度和代码引用；评估图示与语言学习内容，按下表读取必要 reference。需要新实现或实际测试时返回 workflow 对应阶段，随后使用更新后的材料。
5. 形成 `06-final-index-draft.md` 并写回 `index.md`，保留有效 frontmatter 和有价值的用户正文。局部修订只更新相关内容，不因流程要求覆盖整篇。
6. 按本文写作完成标准核对，报告产物和缺口。完整任务由 workflow 接续审查与最终交付；单独写作任务执行适用文章检查后交付本次结果。

## 消费规划与确定布局

候选算法、递进判定、取舍和状态记录以 [`planner`](../oj-solution-planner/SKILL.md) 及其 [`handoff.md`](../oj-solution-planner/references/handoff.md) 为准。本 skill 将规划建议转成正式文章结构，不再维护另一套算法探索规则。

读取 `02` 至 `05` 的实际内容，核对选中方案是否具备适用约束、可执行算法、关键证明、复杂度与代码对应。文件存在或脚本通过不能代替这些内容。仅规划尚无实现时，交回协调者安排必要实现；关键结论未成立时不能称作正解。

按真实关系选择四种布局之一，章节骨架见 [`layouts.md`](../oj-problem-format-spec/references/layouts.md)：

- 子任务递进型呈现有依据的推进主线；存在特例分支时标明其依赖关系，不强行串联。
- 并列多解法型呈现独立完整解法及取舍。
- 暴力到正解型突出朴素方法与被消除的瓶颈。
- 直接正解型省去没有独立教学价值的重复层。

在 `02` 的 `文章结构判定` 中确认最终选择，记录与规划建议不同的取舍。选中布局必须与算法关系一致；算法、文件、语言和子任务数量不能相互代替。正文布局和表格规范集中维护在格式 skill。

### 总览与正文

选定 **子任务递进型** 或 **并列多解法型** 时，在正文 `## 解法路线` / `## 解法总览` 下、各解法展开前放一张总览表。具体列和写法统一见 [`layouts.md`](../oj-problem-format-spec/references/layouts.md#总览表)，不要把两种关系都写成“突破上一层瓶颈”。

- 递进型解释复用了什么、推进了什么；同阶复杂度也可以因取消值域或结构限制而形成有效递进。
- 并列型解释核心观察、适用场景和实现取舍，不虚构先后优化关系。
- 区分“本节针对的子任务”和“算法实际适用范围”。测试点编号只在来源明确时补充；复杂度分析支持的范围与实际测试结果分别记录。

最终正文必须有 `[[TOC]]`、`## 形式化题目`、所选布局和 `## 总结`；每个正式解法拥有自己的 `### 思路`、`### 代码`、`### 复杂度`（递进层可用 `### 复杂度与瓶颈`）。正式主解在对应代码小节使用 `@include-code(./main.<ext>, <lang>)`。完整布局骨架见 [`oj-problem-format-spec/references/layouts.md`](../oj-problem-format-spec/references/layouts.md)。

## 场景路由

只读取当前任务需要的专项资料：

| 场景 | 读取 | 关键产物 |
| --- | --- | --- |
| 完整任务尚未进入写作阶段 | [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md) | 一次性交接，由其协调后续阶段 |
| 所有题解的写作阶段 | [`process-documents.md`](references/process-documents.md) | 过程文档与最终草稿 |
| 需要解释正式暴力层 | [`brute-force.md`](references/brute-force.md) | 基线的教学用途与瓶颈说明 |
| 正文需要说明验证依据 | [`verification.md`](references/verification.md) | 核对验证记录；运行请求交回验证阶段 |
| DP、图、树、网格、搜索、复杂模拟图示 | [`visualization.md`](references/visualization.md) | `viz_render.py`、图表或 `final-visualization.md` |
| 用户目标是 Haskell/Rust/Python 等语言或语法学习 | [`language-learning.md`](references/language-learning.md) | 语言教学文章，不强制暴力 |

格式细节必须读取 `../oj-problem-format-spec/references/frontmatter.md` 和 `layouts.md`；用户明确要求修正旧文章时，额外读取 `migration.md`。旧文章默认不迁移、不批量改写，旧文内容审查交给 `oj-problem-analysis-reviewer`。

## 过程文档与正文要求

`problem-analysis-workspace/` 不存在时创建；核心信息必须记录题意、关键观察/模型、布局判定、解法推导、正确性和边界、复杂度及实现对应关系。复杂题可拆分为专项文件，简单直解题可合并记录；`duipai-report.md`、`final-visualization.md` 和 `viz_render.py` 只在实际使用时生成。具体章节和草稿约束见 `process-documents.md`。

`## 形式化题目` 去除故事背景，只保留数学结构。正文简洁但要解释“为什么这样想到”，不能把过程文档原样倾倒进文章，也不能在 Markdown 中粘贴完整代码。

## 写作完成标准

- 布局判定已复核且有实质依据；代码数量、语言数量和子任务数量不能代替解法关系分析。选直接正解型时说明为何其他候选不值得独立展开。
- 新写或本次明确重写的正文满足共同结构、所选布局和各解法小节要求；递进型/并列型的总览表与正文、代码、适用约束一致。空模板、空标题、缺实现的占位注释不算完整交付。
- frontmatter 的 `description`、`difficulty`、`tags` 已根据题目和代码复核；关系字段只评估是否需要交给 `oj-problem-relation-writer`，不凭记忆编造外部链接。
- 根据规划决定是否独立展示暴力；只有存在、可靠且在任务范围内的基线才引用。跳过重复暴力层时说明教学取舍和实际验证方式，不为填文章骨架新增算法。
- DP 正文在对应思路中有小规模 DP/状态转移表；其他非平凡图示按 `visualization.md` 评估。
- 正确性、边界、复杂度和代码实现互相一致；未运行对拍或样例时如实记录，不声称通过。
- 运行 `python3 scripts/problem-analysis-tools/check_problem.py <题目目录>` 及适用文章检查，确认主解文件存在、引用路径正确、无占位内容和虚构题面信息。现有检查器会跳过未识别的 `legacy` 布局，也未完整检查总览表和过程记录；脚本通过后仍要逐项核对上述结构与内容要求，不能把 `legacy` 当作本次新写或重写文章的豁免。
- `problem-analysis-workspace/` 保持本地忽略。本地交付核对过程记录；共享 CI 或干净检出环境的发布检查只依赖已提交的正文和代码，不要求被忽略的工作区存在。

## 安全与交付

不编造题目标题、来源、约束、接受状态、测试结果或关系；不覆盖用户过程笔记，不把 `brute.cpp` 伪装成正解，不为语言学习或纯直解题强行制造暴力层。完成后简短报告目录、正文与草稿、所选布局、引用的代码和资源、元数据变更、引用的验证证据及仍缺失的材料。写作完成不代表整题测试或最终审查已通过。
