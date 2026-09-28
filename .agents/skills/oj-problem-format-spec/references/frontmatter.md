# Frontmatter 规范

题解文件必须以 YAML frontmatter 开头。新建文章推荐使用以下顺序：

```yaml
---
oj: "luogu"
problem_id: "P1001"
title: ""
description: ""
difficulty: "未知"
date: 2025-11-28 15:41
updated: 2025-11-28 15:41
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source:
---
```

字段含义和维护边界：

- `oj` 用小写 OJ 名称，通常等于目录名；`problem_id` 始终是字符串。
- `title`、`source` 不确定时留空，不编造。
- `description` 是一行 20--80 字（最多 120 字）的核心解法摘要；新建或最终写作必须非空，格式修正旧文无法判断时可为空。不要写题面背景或“经典题/详见下文”等空话。
- `difficulty` 使用 `入门`、`普及-`、`普及`、`普及+/提高-`、`提高`、`提高+/省选-`、`省选/NOI-`、`未知`。新建模板为 `未知`，最终文章应尽量评估，不能可靠判断时保留 `未知`。
- `date` 新建使用本地当前时间，修改旧文保留原日期；`toc` 固定为 `true`。
- `updated` 是“最后修改时间”，格式与 `date` 相同（`YYYY-MM-DD HH:MM`），必须紧跟 `date` 之后。新建时等于 `date`；之后只要题目目录下有**任何**被 Git 跟踪的文件变动（题解正文、代码、测试数据、配图、`talking_with_ai/` 都算），就要把它改成当前时间。首页默认按它降序排列，「最后更新」列也显示它；`.githooks/pre-push` 会拦住改了目录却忘了刷新 `updated` 的提交。旧题缺少该字段时，`npm run check:content` 会报错（可从 Git 历史回填：`python3 scripts/migrate-add-problem-updated.py --apply`）。
- `tags`、`categories` 为数组。本格式 skill 只保证类型和顺序，具体算法标签由写作流程根据仓库已有标签选择。
- `favorite` 必须是布尔个人标记，`favorite_reason` 必须是字符串；新建默认 `false` 和空字符串，修改旧文保留有效值。
- `showAtRbook` 是可选数组，元素为 rbook 文章 id（例如 `fhq-treap`），表示本题解要挂到哪些 rbook 文章下；新建默认空数组。题解内容写完后由 `oj-problem-relation-writer` 或人工填写。
- `pre`、`common`、`recommend` 为可选数组。新建题解应包含空数组；旧文没有时，格式修正不强制添加。具体关系和外部推荐交给 `oj-problem-relation-writer`。

若关系字段存在，顺序为 `categories`、`showAtRbook`、`pre`、`common`、`recommend`、`source`。关系元素格式示例：

```yaml
pre:
  - oj: "luogu"
    problem_id: "P1002"
    reason: "网格路径计数 DP 的基础版本"
recommend:
  - oj: "leetcode"
    problem_id: "62"
    title: "Unique Paths"
    url: "https://leetcode.com/problems/unique-paths/"
    reason: "同模型练习"
    relation: "similar"
```

难度获取优先级：洛谷使用 `python3 scripts/problem-analysis-tools/fetch_problem.py luogu <problem_id> --json` 的官方 `difficulty`：`0` 到 `7` 依次对应上述八档；其他 OJ 使用可靠的官方 rating 换算，无法判断才按复杂度和知识点估计。不要凭记忆编造难度。
