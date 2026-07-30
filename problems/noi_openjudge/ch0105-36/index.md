---
oj: "noi_openjudge"
problem_id: "ch0105-36"
title: "计算多项式的值"
description: "递推维护 x 的幂并累加，计算等比多项式 1+x+...+x^n。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "数学", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/36/
---

[[TOC]]

### 题意

计算多项式 $1+x+x^2+\cdots+x^n$ 的值，结果保留两位小数。

### 思路

令 `power` 表示当前的 $x^i$。初始时 `power = 1` 对应 $x^0$，每轮先乘以 `base` 得到下一次幂，再加入总和。这样不需要反复调用幂函数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

连续幂相邻两项只相差一次乘法，循环维护当前幂是最稳定的实现方式。
