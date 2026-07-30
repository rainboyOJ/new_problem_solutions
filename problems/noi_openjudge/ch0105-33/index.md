---
oj: "noi_openjudge"
problem_id: "ch0105-33"
title: "计算分数加减表达式的值"
description: "按分母奇偶决定正负号，线性累加交错调和级数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "数学", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/33/
---

[[TOC]]

### 题意

计算交错级数 $1-1/2+1/3-1/4+\cdots+(-1)^{n-1}/n$，结果保留四位小数。

### 思路

第 $i$ 项的分母就是 $i$。奇数项为正、偶数项为负，因此可由 `denominator % 2` 决定 `sign`，然后累加 `sign / denominator`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

交错求和中，项号的奇偶性通常就是最直接的符号状态。
