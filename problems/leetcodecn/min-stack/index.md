---
oj: "leetcodecn"
problem_id: "min-stack"
title: "最小栈"
description: "每个元素同时保存当前值和截至该层的最小值，getMin 直接读栈顶的 min 字段。"
difficulty: "普及-"
date: 2026-07-29 12:05
toc: true
tags: ["栈", "数据结构"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/min-stack/
---

[[TOC]]

### 题意

设计一个栈，支持 `push`、`pop`、`top`、`getMin` 四个操作，`getMin` 要求 $O(1)$。

### 思路

核心思路：栈中每个元素同时保存"当前值"和"截至该层的最小值"。`push` 时，`min` 字段取当前值与栈顶 `min` 的较小值；`getMin` 直接读栈顶的 `min` 字段。

这样 `pop` 后新的栈顶 `min` 自然就是剩余元素的最小值，无需额外维护。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：每个操作 $O(1)$。
- 空间复杂度：$O(n)$，每个元素存一对值。

### 总结

最小栈的关键是"每层同时保存当前值与截至该层的最小值"，使得 `pop` 后最小值自动更新，不需要辅助栈或重新扫描。
