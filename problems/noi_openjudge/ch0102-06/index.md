---
oj: "noi_openjudge"
problem_id: "ch0102-06"
title: "浮点数向零舍入"
description: "先按单精度读入，再用 int 向零截断得到整数部分。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/06/
---

[[TOC]]

### 题意

读入一个单精度浮点数，向零舍入为整数。正数舍去小数部分，负数也向零靠近。

### 思路

Python 的 `int(value)` 正是向零截断：`int(2.9)` 为 `2`，`int(-2.9)` 为 `-2`，不要用 `round` 或 `math.floor`。题目指定单精度，代码先用 `struct` 完成与 C++ `float` 相同的一次单精度舍入，再转换为整数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

记住 Python 的 `int` 是向零截断；它与负数的下取整不同。
