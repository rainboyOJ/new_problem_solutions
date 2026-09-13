---
description: 按仓库规范写或补完 problems/<oj>/<id>/index.md 题解
---
题目目录：优先用用户消息里给出的路径；消息里没给就用当前工作目录。

目标：把该题目的 `index.md` 写成（或补成）一篇能直接发布的正文。

先读这些文件，规范以它们为准，不要凭印象写：

- `.agents/skills/oj-problem-analysis-writer/SKILL.md`（写作流程与布局判定，最高优先级）
- `.agents/skills/oj-problem-format-spec/SKILL.md` 及其 `references/`（frontmatter 与正文骨架）
- `.agents/skills/oj-cpp-competitive-style/SKILL.md`（C++ 风格）
- 题目目录内的 `problem.md`、`main.*`、`brute.cpp`、`gen.py`、已有 `index.md`、`problem-analysis-workspace/*.md`

必须守住的几条：

- 最终正文要有 `[[TOC]]`、`## 形式化题目`、所选布局的正文、`## 总结`；每个正式解法有自己的 `### 思路`、`### 代码`、`### 复杂度`。
- 正式主解必须在对应代码小节用 `@include-code(./main.<ext>, <lang>)` 引入，不要在 Markdown 里粘贴完整代码。
- 布局判定写在 `problem-analysis-workspace/02-observation-and-model.md`，依据实际解法和约束选「直接正解型 / 暴力到正解型 / 并列多解法型 / 子任务递进型」，不要按简单困难选。
- frontmatter 保留有效字段，`description`、`difficulty`、`tags` 按题目和代码复核；不编造来源、约束、测试结果、通过状态。
- 已有的过程笔记和用户正文优先保留，不要覆盖。

完成后报告：改了哪些文件、选了什么布局、frontmatter 改了什么、跑没跑样例或对拍、还缺什么材料。
