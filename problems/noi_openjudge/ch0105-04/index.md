---
oj: "noi_openjudge"
problem_id: "ch0105-04"
title: "求整数的和与均值"
description: "一次累计 n 个整数，同时输出总和和五位小数均值。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/04/
---

[[TOC]]

### 题意

读入 $n$ 个整数，输出它们的和与平均值，平均值保留五位小数。

### 思路

总和只需累计一次。平均值直接由 `total / count` 得到，最后在同一条 f-string 中输出总和和 `.5f` 格式化结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

需要总和和均值时，不必保存全部输入；总和与数量已足够。
