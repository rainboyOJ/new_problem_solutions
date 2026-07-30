---
oj: "noi_openjudge"
problem_id: "ch0109-07"
title: "不与最大数相同的数字之和"
description: "先确定最大值，再累加所有不等于最大值的序列元素。"
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
source: http://noi.openjudge.cn/ch0109/07/
---

[[TOC]]

### 题意

求整数序列中所有不等于最大值的元素和。

### 思路

先用 `max` 找出最大值，再生成器求和时过滤所有等于它的元素。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，序列空间为 $O(n)$。

### 总结

题意要求排除的是所有最大值，不只是其中一个。
