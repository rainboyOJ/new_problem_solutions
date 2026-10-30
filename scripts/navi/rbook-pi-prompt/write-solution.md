---
description: 按仓库规范写或补完 problems/<oj>/<id>/index.md 题解
argument-hint: "[题目目录]"
---
题目目录：${@:-优先用用户消息里给出的路径；消息里没给就用当前工作目录。}

目标：把该题目的 `index.md` 写成（或补成）一篇能直接发布的正文。

先读仓库 `AGENTS.md`、README 第 6 节、`problems/CONTEXT.md`，再读取：

- `.agents/skills/oj-problem-workflow/SKILL.md`（单题总入口）
- 题目目录内的 `problem.md`、已有源码、样例、`index.md` 与过程记录

按 workflow 判断任务终点和当前阶段，再加载对应专项 skill。可靠材料直接复用；规划、实现、验证、写作与审查分别留下证据。专项 skill 不反向重启总流程，发现缺口按 workflow 返回对应阶段。

必须守住的几条：

- 最终正文要有 `[[TOC]]`、`## 形式化题目`、所选布局的正文、`## 总结`；每个正式解法有自己的 `### 思路`、`### 代码`、`### 复杂度`。
- `## 形式化题目` 用树、点、权值、颜色这类抽象对象，不搬题面故事词；每条操作写成「中文动作 + 形式化式子」两层（先一句话说在做什么，再给式子）。
- 正式主解必须在对应代码小节用 `@include-code(./main.<ext>, <lang>)` 引入，不要在 Markdown 里粘贴完整代码。
- 布局判定写在 `problem-analysis-workspace/02-observation-and-model.md`，依据实际解法和约束选「直接正解型 / 暴力到正解型 / 并列多解法型 / 子任务递进型」，不要按简单困难选。
- frontmatter 保留有效字段，`description`、`difficulty`、`tags` 按题目和代码复核；不编造来源、约束、测试结果、通过状态。
- 已有的过程笔记和用户正文优先保留，不要覆盖。

完成后报告：改了哪些文件、选了什么布局、frontmatter 改了什么、跑没跑样例或对拍、还缺什么材料。
