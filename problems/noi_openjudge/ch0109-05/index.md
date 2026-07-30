---
oj: "noi_openjudge"
problem_id: "ch0109-05"
title: "最大值和最小值的差"
description: "直接取整数序列的最大值与最小值，并输出二者之差。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0109/05/
---

[[TOC]]

### 题意

输出整数序列最大值减最小值。

### 思路

Python 的 `max` 和 `min` 可直接得到两个极值，再相减即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，序列空间为 $O(n)$。

### 总结

极值差问题只依赖最大值和最小值。
