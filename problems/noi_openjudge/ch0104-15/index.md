---
oj: "noi_openjudge"
problem_id: "ch0104-15"
title: "最大数输出"
description: "使用内建 max 从三个整数中取最大值。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/15/
---

[[TOC]]

### 题意

输入三个整数，输出最大值。

### 思路

`max` 可以直接接收可迭代对象。`map(int, input().split())` 产生三个整数，交给 `max` 即可，不必手写两次比较。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

元素个数固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

求一组数的最值优先使用 `max` 或 `min`，语义清楚且不会漏比较分支。
