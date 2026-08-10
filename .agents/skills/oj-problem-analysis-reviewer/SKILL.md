---
name: oj-problem-analysis-reviewer
description: Review and audit existing Chinese OJ problem explanations for this repository. Use this skill when the user asks to review, audit, check quality, 审稿, 检查题解质量, 判断题解是否讲清楚, improve an existing problems/<oj>/<problem_id>/index.md, or find issues in a written OJ problem analysis. This skill focuses on whether readers can learn the problem from the article; it does not write a new explanation from scratch.
---

# OJ 题目解析审稿

这个 skill 专门审查已有题目解析是否能让读者学会这道题。

默认只审稿并输出报告；只有用户明确要求“修复”“改写”“应用建议”“直接改”时，才编辑 `index.md`。

## 边界

本 skill 负责：

- 审查已有 `problems/<oj>/<problem_id>/index.md` 的讲解质量。
- 判断题解是否存在跳步、只贴代码、样例解释不足、图表说明不足等问题。
- 对照 `main.cpp` / `brute.cpp` 检查文字和代码是否能互相对应。
- 检查 `description`、`tags`、`pre` / `common` / `recommend` 的表达是否有明显质量问题。
- 调用已有检查工具提供基础信号。
- 在用户明确要求修复时，修改 `index.md` 并尽量保持原文风格。

本 skill 不负责：

- 从零写一篇题解。
- 发明新的算法解法。
- 维护题目关系字段的候选生成。
- 渲染关系图或样例可视化。
- 默认修改 `main.cpp` 或 `brute.cpp`。

从零写题解使用 `oj-problem-analysis-writer`。
格式骨架使用 `oj-problem-format-spec`。
样例可视化使用 `oj-sample-visualizer`。
题目关系和推荐练习使用 `oj-problem-relation-writer`。

## 读取顺序

审稿时优先读取：

1. `problems/<oj>/<problem_id>/index.md`
2. `problems/<oj>/<problem_id>/main.cpp`
3. `problems/<oj>/<problem_id>/brute.cpp`
4. `problems/<oj>/<problem_id>/problem.md`
5. `problems/<oj>/<problem_id>/problem-analysis-workspace/*.md`
6. `.agents/skills/oj-problem-format-spec/SKILL.md`

如果只是审稿，不要修改文件。

如果用户要求修复，修改前必须读取 `oj-problem-format-spec`，并保留已有有价值的用户内容。

## 工具检查

审稿时先运行已有确定性工具：

```bash
python3 scripts/problem-analysis-tools/check_problem.py problems/<oj>/<problem_id>
python3 scripts/problem-analysis-tools/check_relations.py problems/<oj>/<problem_id>
```

如果以后存在下面的质量检查脚本，也要运行：

```bash
python3 scripts/problem-analysis-tools/check_analysis_quality.py problems/<oj>/<problem_id>
```

工具报告是审稿输入，不是最终结论。不要机械复述工具输出，要结合题解内容判断是否真的影响读者理解。

## 审稿维度

按“读者能否学会”组织审稿，而不是只按文件结构罗列。

### 学习目标

检查：

- 读者是否能明白题目要求什么。
- 题解是否让读者理解计算任务的数学本质，不依赖输入输出格式细节。
- 是否说明最后要解决的核心目标。

常见问题：

- 形式化题目保留了故事背景或无关信息，不像数学题目。
- 没有解释约束为什么影响算法选择。

### 推导链条

检查：

- 是否从朴素想法讲到优化。
- 是否解释关键观察从哪里来。
- 是否直接跳到结论。
- 是否说明为什么这个算法适用。

常见问题：

- “显然可以 DP”但没有定义状态来源。
- “用贪心即可”但没有交换、反证或不变式说明。
- “建图跑最短路”但没有解释节点和边的含义。

### 状态和模型

按题型重点检查：

- DP：状态定义、转移来源、初始化、遍历顺序、答案位置。
- 图论：节点含义、边含义、方向/权重、遍历或松弛逻辑。
- 贪心：选择标准、为什么局部最优能推出全局最优。
- 搜索：状态、扩展方式、剪枝条件、正确性风险。
- 数据结构：维护的信息、操作含义、复杂度来源。

### 代码对应

检查：

- 正文中的变量名和 `main.cpp` 是否能对应。
- 核心循环是否在正文中解释。
- 边界处理是否只藏在代码里。
- `brute.cpp` 是否说明了朴素思路或对拍用途。

不要做逐行代码讲解。重点是“思路和实现之间是否接得上”。

### 样例和可视化

检查：

- 是否解释样例中关键数据。
- 图片、表格、Mermaid、Graphviz、SVG 是否有图前说明和图后解释。
- DP 表是否说明行、列、单元格含义。
- 可视化是否服务于理解，而不是装饰。

如果题目明显适合可视化但没有可视化，只作为建议，不作为必须修。

### 元数据

检查：

- `description` 是否具体描述核心方法，而不是“经典题”“模板题”等空话。
- `difficulty` 是否缺失、是否为标准枚举、是否和题解中的算法复杂度与知识点明显不匹配。
- Luogu 题目的 `difficulty` 是否与官方 `difficulty` 字段一致（id→枚举映射见 `oj-problem-format-spec`）；凭印象猜测的难度视为质量问题。
- `tags` 是否和题解内容一致。
- `pre` / `common` / `recommend` 的 `reason` 是否具体。
- `recommend.reason` 是否说明推荐关系，而不是只有“类似题”。

关系字段的具体维护仍由 `oj-problem-relation-writer` 负责。

## 报告格式

默认输出中文审稿报告，按严重程度排序：

```text
必须修
- [推导链条] ## 思路 直接给出结论，没有解释为什么可以使用这个模型。

建议修
- [样例和可视化] 第 42 行 DP 表后缺少说明，读者不知道当前格从哪里来。

可选优化
- [元数据] description 可以更具体，建议写出“用什么维护什么”。

已通过
- frontmatter 字段完整。
- main.cpp 引用存在。
```

规则：

- 每条问题要指出位置或章节。
- 每条问题要说明为什么影响读者理解。
- 能给改法时，给具体改法，不写泛泛建议。
- 如果没有明显问题，明确说“未发现必须修的问题”，并说明剩余风险。

## 修复模式

只有用户明确要求修复时才编辑。

修复原则：

- 优先小改，不整篇重写。
- 保留用户原有表达中有价值的部分。
- 不改变 `@include-code(./main.cpp, cpp)` 和 `@include-code(./brute.cpp, cpp)` 的规范位置，除非原文明显错误。
- 不编造题面或算法事实；不确定时写入审稿报告，不写进正式正文。
- 修改后运行 `check_problem.py`；如果存在 `check_analysis_quality.py`，也运行它。

修复完成后说明：

- 改了哪些章节。
- 哪些问题已解决。
- 哪些问题仍需人工确认。
