---
oj: "luogu"
problem_id: "P2866"
title: "[USACO06NOV] Bad Hair Day S"
description: "从左到右维护严格递减高度栈，当前入场前仍在栈中的牛都能看到它。"
difficulty: "普及/提高-"
date: 2026-06-18 16:33
toc: true
tags: ["单调栈", "栈", "USACO", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2866
---

[[TOC]]

### 题意

每头牛能看到右侧连续比自己矮的牛，直到遇到第一头不矮于自己的牛。求所有可见数量之和。

### 思路

从左到右加入当前牛。栈中保存还没有被更高或等高牛挡住的历史高度，并保持严格递减。

当前高度到来时，先弹出所有 `<= current` 的栈顶：这些牛会被当前牛挡住，也不能看到当前牛。剩余栈里的每头牛都比当前牛高且中间没有遮挡，因此答案增加 `len(stack)`，再压入当前高度。

### Python 知识

- Python 列表尾部 `append/pop` 就是高效栈。
- 只保存高度，不需要保存下标或完整序列。
- `answer += len(stack)` 一次统计所有能看到当前牛的历史牛。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

单调栈保留“仍可能继续向右看”的牛，每头牛最多入栈、出栈一次。
