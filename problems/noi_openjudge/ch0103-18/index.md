---
oj: "noi_openjudge"
problem_id: "ch0103-18"
title: "等差数列末项计算"
description: "利用 an=a1+(n-1)(a2-a1) 直接计算等差数列第 n 项。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/18/
---

[[TOC]]

### 题意

给出等差数列前两项和位置 $n$，求第 $n$ 项。

### 思路

公差为 $a_2-a_1$，第 $n$ 项是 $a_1+(n-1)(a_2-a_1)$。不用循环累加，直接代入通项公式即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

等差数列首项、末项题先写公差，再写通项，避免把 $n-1$ 错写成 $n$。
