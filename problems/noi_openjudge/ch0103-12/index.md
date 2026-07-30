---
oj: "noi_openjudge"
problem_id: "ch0103-12"
title: "计算球的体积"
description: "按 V=4/3*pi*r^3 和题设 pi=3.14 计算体积。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/12/
---

[[TOC]]

### 题意

给定球半径，取 $\pi=3.14$ 计算体积，保留 2 位小数。

### 思路

直接计算 $V=\frac43\pi r^3$。Python 的 `**3` 表示三次方，`4 / 3` 是浮点除法，不会发生 C++ 整数除法截断。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

写体积公式时要保留 $4/3$ 的浮点含义，并使用题面规定的圆周率。
