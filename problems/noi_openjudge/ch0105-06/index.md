---
oj: "noi_openjudge"
problem_id: "ch0105-06"
title: "整数序列的元素最大跨度值"
description: "读取序列后用 max-min 计算最大跨度。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/06/
---

[[TOC]]

### 题意

给定非负整数序列，输出最大值减去最小值。

### 思路

跨度定义就是 `max(numbers) - min(numbers)`。本题数据规模只有 1000，读成列表后分别求最大和最小值最直接。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(n)$。

### 总结

序列的极差等于最大值减最小值，是 `max` 和 `min` 的直接应用。
