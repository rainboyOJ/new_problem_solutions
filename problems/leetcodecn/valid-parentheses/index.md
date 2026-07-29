---
oj: "leetcodecn"
problem_id: "valid-parentheses"
title: "有效的括号"
description: "栈匹配：左括号入栈，右括号必须与栈顶严格配对，最终栈空则合法。"
difficulty: "入门"
date: 2026-07-29 12:02
toc: true
tags: ["栈", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/valid-parentheses/
---

[[TOC]]

### 题意

给定仅含括号的字符串，判断是否有效：每个右括号与最近未匹配的左括号类型相同且顺序正确。

### 思路

左括号入栈，遇到右括号时栈顶必须与之匹配：`)` 对应 `(`，`]` 对应 `[`，`}` 对应 `{`。不匹配或栈空则非法。扫描结束后栈必须为空（所有左括号都已闭合）。

关键：栈顶始终是"最近一个未匹配的左括号"，右括号只能匹配栈顶——这对应括号的就近闭合规则。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，每个字符一次入栈或弹出。
- 空间复杂度：$O(n)$，栈最深存所有左括号。

### 总结

括号匹配是栈的基础应用：左括号"等待匹配"，右括号"检查并消解栈顶"。栈的 LIFO 性质天然保证就近闭合规则。
