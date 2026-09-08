---
name: oj-problem-format-spec
description: Standardize the writing format and Markdown skeleton for this repository's Chinese OJ problem explanation ebook. Use this skill whenever the user asks about 题解格式, 题目解析格式规范, OJ article skeletons, problems/<oj>/<problem_id>/index.md, frontmatter, section titles, @include-code, or formatting existing problem notes. This skill only defines article structure and formatting; it does not write algorithm analysis or solve the problem.
---

# OJ 题目解析格式规范

本 skill 只维护 `problems/<oj>/<problem_id>/index.md` 的结构、frontmatter、代码引用和 Markdown 组织方式，不推导算法、不审查证明，也不维护题目关系。算法正文由 `oj-problem-analysis-writer` 填写；关系元数据由 `oj-problem-relation-writer` 维护；Markdown 扩展语法以 `rbook-markdown` 为准。

## 工作边界

- 新建题解使用 `scripts/problem-analysis-tools/template/index.md` 或 `new-problem.py` 生成的目录骨架。
- `new-problem.py` 只提供布局中立的材料骨架；不能据此假定正文固定为“思路/代码/复杂度”。最终布局必须根据解法关系选择。
- 共同外层为 `[[TOC]]`、`## 形式化题目` 和 `## 总结`。中间正文只能采用 [四种布局](references/layouts.md) 之一。
- 正式解法的代码放在自身的 `### 代码` 中，使用 `@include-code(...)`，不把完整代码粘进 Markdown。
- 旧文章默认只保留原正文；只有用户明确要求格式修正或迁移时才读取 [迁移规则](references/migration.md)。

需要字段或布局细节时，按场景读取：

- frontmatter、难度、关系字段：[`references/frontmatter.md`](references/frontmatter.md)
- 四种布局、章节约束、代码嵌入和公式：[`references/layouts.md`](references/layouts.md)
- 用户明确要求修正旧文章：[`references/migration.md`](references/migration.md)

## 最小工作流

1. 确认目标目录 `problems/<oj>/<problem_id>/`。目录或 `index.md` 不存在时，调用 `python3 scripts/problem-analysis-tools/new-problem.py <problem URL>`；已有目录不得重建或覆盖。
2. 读取本文档及需要的 references，再读取题目材料、代码和过程文档。不要把本 skill 当作算法解析来源。
3. 根据解法关系选择一种布局，重写骨架时只改正文骨架，保留有效 frontmatter 和用户正文。
4. 检查每个正式解法都有自己的 `### 代码`，正式主解引用同目录 `main.<ext>`；空内容使用 HTML 注释，不使用可见的 TODO/“待补充”。
5. 完成后运行仓库检查工具或相应测试，并确认 Markdown 中没有完整代码块、错误相对路径或虚构字段。

## Grill-Me

用户明确要求 `grill me` 时，一次只问一个问题，优先围绕职责边界、布局判定、frontmatter 最小字段、代码引用和旧文保留策略；能从仓库判断的内容不问用户。

推荐问题顺序：

1. 这个 skill 是否只管格式、不管解析内容？
2. 哪些共同章节固定，哪些正文标题由解法关系决定？
3. 是否强制最小 frontmatter 字段？
4. 是否统一使用 `@include-code(...)` 嵌入代码？
5. 题目应使用哪一种正文布局，判定依据是什么？
6. 空章节是否使用 HTML 注释占位？
7. 是否负责文件命名和存放路径？
8. 修改已有题解时，是强制套模板还是只修正格式？
9. 是否把 Mermaid、Graphviz、二维表格等可视化内容纳入格式规范？
10. 是否在 frontmatter 中加入 `description` 作为题解核心摘要？

## 交付检查

- 文件路径和 frontmatter 位于 `problems/<oj>/<problem_id>/index.md` 开头。
- frontmatter 字段顺序与字段类型符合 [`frontmatter.md`](references/frontmatter.md)，新建文章的 `description`、`difficulty`、`pre`、`common`、`recommend` 已处理。
- 正文有 `[[TOC]]`、`## 形式化题目`、所选布局和 `## 总结`，没有一级标题。
- 布局所需的章节、代码引用和占位注释完整；主解的 `@include-code(./main.<ext>, <lang>)` 指向存在的文件。
- 图表、公式和其他扩展语法遵守 `rbook-markdown` 及布局 reference；本 skill 不负责判断是否需要图示。

完成后只报告修改文件、是新建还是格式修正、是否保留原正文，以及仍缺失的字段或代码文件。
