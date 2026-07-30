---
oj: "noi_openjudge"
problem_id: "ch0104-18"
title: "点和正方形的关系"
description: "横纵坐标绝对值都不超过 1 时，点在正方形及其边界内。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["几何", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/18/
---

[[TOC]]

### 题意

判断点是否在顶点为 $(\pm1,\pm1)$ 的正方形内，边界也算在内。

### 思路

正方形轴对齐，横纵坐标必须分别落在 $[-1,1]$。用 `abs(x) <= 1 and abs(y) <= 1` 同时包含四条边和四个顶点。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

轴对齐矩形的点包含问题可拆成两个独立坐标区间判断。
