---
oj: "shumeng"
problem_id: "CSP202503A"
title: "数值积分"
description: "找到区间内第一个偶数坐标，按步长 2 枚举函数值并乘以坐标间距。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503A
---

[[TOC]]

### 题意

给定二次函数 `f(x)=x^2+bx+c` 和整数区间 `[l,r]`，取区间内所有偶数坐标点，计算函数值之和，再乘以步长 `2`。

### 思路

从 `l` 开始调整到第一个偶数 `first`，然后以步长 `2` 枚举 `first, first+2, ...`，累加 `x*x+b*x+c`，最后乘以 `2`。题目约束很小，直接模拟即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设区间内偶数点数量为 `k`，时间复杂度为 `O(k)`，空间复杂度为 `O(1)`。

### 总结

这道题的关键是正确处理第一个偶数点和相邻采样点之间的步长 `2`。
