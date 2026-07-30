---
oj: "noi_openjudge"
problem_id: "ch0103-16"
title: "计算线段长度"
description: "用 math.hypot 计算两点坐标差的欧几里得距离。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "几何", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/16/
---

[[TOC]]

### 题意

输入平面两点坐标，输出线段长度，保留 3 位小数。

### 思路

距离公式是 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。`math.hypot(dx, dy)` 直接表达该公式，也比手写平方根更清晰。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

二维两点距离优先记住 `math.hypot`，它避免手写平方和开方。
