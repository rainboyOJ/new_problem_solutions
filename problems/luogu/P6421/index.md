---
oj: "luogu"
problem_id: "P6421"
title: "[COCI 2008/2009 #2] RESETO"
description: "按埃氏筛的实际删数顺序模拟，统计第 k 次真正删除的整数。"
difficulty: "普及-"
date: 2026-06-18 20:56
toc: true
tags: ["模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6421
---

[[TOC]]

### 题意

按题目给定的埃拉托色尼筛法删除 `2..n` 中的数，要求输出第 `k` 个被删除的整数。

### 思路

先看一个可以直接验证想法的朴素解：

每一轮先找到当前最小的未删数 `p`，再删掉 `p` 及其所有还没删掉的倍数。

@include-code(./brute.cpp, cpp)

对本题来说，直接模拟已经足够。
实现时可以把外层写成 `p = 2..n` 顺序扫描：

- 如果 `p` 已经被删掉，就跳过；
- 如果还没删掉，就按步长 `p` 枚举倍数并删数。

每当真正删掉一个新数，就把计数加一；当计数达到 `k` 时，这个数就是答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

本题规模很小，直接模拟完全足够。
空间复杂度是 $O(n)$。

### 总结

这题的关键不是求素数，而是严格按照筛法的“删数顺序”去模拟。
