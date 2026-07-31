---
oj: "shumeng"
problem_id: "CSP202312B"
title: "因子化简"
description: "试除分解每个 n，统计各质因子的指数，只保留指数不小于阈值 k 的完整质因数幂。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["数论", "质因数分解", "枚举"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202312B
---

[[TOC]]

### 题意

对正整数 $n$ 做质因数分解。给定阈值 $k$，指数小于 $k$ 的质因数幂全部删除，指数不小于 $k$ 的完整保留；如果全部删除则输出 $1$。

### 思路

先看试除分解的朴素做法：

@include-code(./brute.cpp, cpp)

从 $2$ 开始枚举可能的质因子 `prime`。当 `n % prime == 0` 时不断除去它并统计指数 `exponent`；如果 `exponent >= k`，就把 `prime` 的相同次数乘入答案，否则忽略这一整项。

试除结束后，如果剩余 `value > 1`，它是一个指数为 $1$ 的质因子。本题 $k>1$，所以它不会被保留；代码保留了 `k<=1` 时的通用处理。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

单次查询最多试除到 $\sqrt n$，时间复杂度为 $O(\sqrt n)$，空间复杂度为 $O(1)$；全部查询为 $O(q\sqrt n)$。

### 总结

因子是否保留只取决于它的指数，必须先完整统计一个质因子的次数，再决定是否乘回。试除后剩余的大质因子只能出现一次，指数判断是本题容易遗漏的边界。
