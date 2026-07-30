---
oj: "noi_openjudge"
problem_id: "ch0105-05"
title: "最高的分数"
description: "用 max 在一行 n 个成绩中直接取最高分。"
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
source: http://noi.openjudge.cn/ch0105/05/
---

[[TOC]]

### 题意

读入 $n$ 个成绩，输出最高分。

### 思路

题目保证至少有一名学生，因此可将 `map(int, input().split())` 直接传入 `max`。迭代器逐个提供成绩，不需要额外保存列表。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

求单个最值时，内建 `max` 比手写初值和循环更新更简洁。
