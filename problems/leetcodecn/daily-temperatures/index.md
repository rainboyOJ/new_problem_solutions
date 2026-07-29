---
oj: "leetcodecn"
problem_id: "daily-temperatures"
title: "每日温度"
description: "单调栈保存尚未遇到更高温度的下标，弹出时计算距离即为等待天数。"
difficulty: "普及+/提高"
date: 2026-07-29 12:10
toc: true
tags: ["单调栈", "栈"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/daily-temperatures/
---

[[TOC]]

### 题意

给定每日温度数组，对每一天找出下一个更高温度出现在几天后。

### 思路

从左到右扫描，维护单调栈（从栈底到栈顶温度递减）。栈中保存尚未遇到更高温度的下标：

- 当前温度 `temps[i]` 比栈顶温度高时，栈顶位置找到了答案：`answer[st.top()] = i - st.top()`，弹出栈顶。
- 重复直到栈顶温度不低于当前，然后压入当前下标。

扫描结束后栈中剩余的下标没有更高温度，答案保持 `0`。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，每个下标最多入栈、出栈一次。
- 空间复杂度：$O(n)$，栈最多存所有下标。

### 总结

单调栈的核心是"栈中保存尚未解决的候选"，遇到更大的值时逐个结算。本题栈存下标而非值，弹出时用下标差计算距离。
