---
oj: "luogu"
problem_id: "CF912E"
title: "Prime Gift"
description: "Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/912E，本页仅保留入口。"
difficulty: "省选/NOI-"
date: 2026-07-16 20:10
toc: true
tags: ["Meet-in-the-Middle", "二分答案", "数论"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF912E
---

[[TOC]]

### 题意

给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。完整教学解析（含 Python 版本与思考过程）已迁移至：

- [[problem: codeforces,912E]] · [CF912E Prime Gift 题解](https://codeforces.com/problemset/problem/912/E)

### 思路

把质数交错分到两组，分别 DFS 枚举不超过 $10^{18}$ 的乘积；二分答案 `limit`，用只向左移动的右指针统计 `left[i] * right[j] <= limit` 的配对数。乘法比较写成 `left > limit / right`，避免 64 位溢出。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设两边乘积数为 $A,B$，生成与排序 $O(A\log A+B\log B)$，二分计数 $O((A+B)\log 10^{18})$。

### 总结

完整解析已迁移至 [[problem: codeforces,912E]]。
