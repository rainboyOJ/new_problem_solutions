---
oj: "noi_openjudge"
problem_id: "ch0111-02"
title: "二分法求函数的零点"
description: "在函数值异号且根唯一的区间上二分，逐步缩小零点范围。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/02/
---

[[TOC]]

### 题意

已知五次函数在区间 $[1.5, 2.4]$ 内恰有一个零点，输出该零点并保留六位小数。

### 思路

区间端点函数值异号，且根唯一。每次取中点，根据中点函数值的符号保留仍包含零点的一半区间。固定迭代 100 次后误差远小于输出精度。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定进行 100 次二分，时间复杂度为 $O(1)$，空间复杂度为 $O(1)$。

### 总结

连续函数的唯一零点可用端点异号性质定位，二分时无需显式求解方程。
