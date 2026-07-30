---
oj: "noi_openjudge"
problem_id: "ch0103-14"
title: "大象喝水"
description: "计算圆桶体积后对 20000 立方厘米向上取整。"
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
source: http://noi.openjudge.cn/ch0103/14/
---

[[TOC]]

### 题意

圆桶体积为 $\pi r^2h$，大象至少要喝 20 升，即 20000 立方厘米水，求最少桶数。

### 思路

先计算一桶体积，再计算 $20000/V$。题目问“至少”，所以答案必须向上取整，Python 直接使用 `math.ceil`。圆周率按题设取 `3.14159`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

“至少需要多少个完整单位”是向上取整信号，不能只取整数部分。
