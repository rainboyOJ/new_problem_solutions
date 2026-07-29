---
oj: "leetcodecn"
problem_id: "longest-valid-parentheses"
title: "最长有效括号"
description: "栈保存未匹配位置，弹出后用栈顶计算有效长度，栈空时压入当前右括号作为新边界。"
difficulty: "提高+/省选-"
date: 2026-07-29 12:48
toc: true
tags: ["栈", "动态规划", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/longest-valid-parentheses/
---

[[TOC]]

### 题意
求最长有效括号子串的长度。

### 思路
栈中保存下标。初始压入 `-1` 作为虚拟边界。遇到 `(` 压入下标；遇到 `)` 弹出栈顶，若栈空则压入当前下标作为新边界，否则用当前下标减去栈顶计算有效长度。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(n)$。

### 总结
栈解法的关键是栈中始终保存"最后一个未被匹配的右括号下标"作为边界。弹出后栈顶就是有效子串的起点前一个位置，差值即为长度。
