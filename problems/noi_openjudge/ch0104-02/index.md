---
oj: "noi_openjudge"
problem_id: "ch0104-02"
title: "输出绝对值"
description: "用内建 abs 求浮点数绝对值，再以 .2f 输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/02/
---

[[TOC]]

### 题意

输出一个浮点数的绝对值，保留 2 位小数。

### 思路

Python 内建 `abs` 同时适用于整数和浮点数。`f"{abs(number):.2f}"` 保证输出两位小数，包括必要的末尾零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

绝对值用 `abs`，固定小数位用 `.2f`，不必手写正负分支。
