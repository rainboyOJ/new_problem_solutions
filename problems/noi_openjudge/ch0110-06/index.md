---
oj: "noi_openjudge"
problem_id: "ch0110-06"
title: "整数奇偶排序"
description: "分别排序奇数和偶数，再按奇数降序、偶数升序拼接输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "分类讨论", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/06/
---

[[TOC]]

### 题意

将十个整数重新排列：奇数在前且从大到小，偶数在后且从小到大。

### 思路

按奇偶性将数分成两个序列。奇数调用 `sorted(..., reverse=True)` 得到降序，偶数正常升序。最后用扩展参数 `print(*odds, *evens)` 按要求将两段连在一起输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设输入规模为 $n$，时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

先分类再分别排序，是处理“不同类别有不同顺序”的直接方法。
