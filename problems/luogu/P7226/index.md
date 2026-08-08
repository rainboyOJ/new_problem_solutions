---
oj: "luogu"
problem_id: "P7226"
title: "[COCI 2015/2016 #3] POT"
description: "拆出个位幂次后直接计算 num^p 并累加。"
difficulty: "入门"
date: 2026-06-18 20:15
toc: true
tags: ["数学", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P7226
---

[[TOC]]

### 题意

给出 `n` 个数 `q_i`，每个数都可以拆成：

- `num_i`：前面的整数部分
- `p_i`：最后一位的幂次

要求恢复并计算原式 `num_i ^ p_i` 的总和。

### 思路

先看一个可以直接验证想法的朴素解：

这题直接按题意拆分即可。
对每个 `q_i`，先用 `q_i / 10` 还原出 `num_i`，再用 `q_i % 10` 还原出 `p_i`，最后计算 `num_i ^ p_i` 并累加。

@include-code(./brute.cpp, cpp)

因为 `n <= 10`，而且 `p_i` 只有一位数，所以这里根本不需要额外优化。
把幂运算写成一个小循环，代码会最直观。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个数最多做 9 次乘法，所以总时间复杂度是 $O(n)$。
空间复杂度是 $O(1)$。

### 总结

这题的核心就是按位拆分输入，恢复出原来的底数和幂次，然后直接累加。
