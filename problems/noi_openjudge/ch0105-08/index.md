---
oj: "noi_openjudge"
problem_id: "ch0105-08"
title: "多边形内角和"
description: "从 (n-2)*180 的内角和中减去已知 n-1 个角。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/08/
---

[[TOC]]

### 题意

已知 $n$ 边形的 $n-1$ 个内角，求最后一个内角。

### 思路

多边形内角和是 $(n-2)\times180$。从总和中减去所有已知角度之和，剩下的就是未知角。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

已知整体和与部分和时，未知部分直接等于“整体减已知部分”。
