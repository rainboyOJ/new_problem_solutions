---
oj: "noi_openjudge"
problem_id: "ch0103-02"
title: "计算(a+b)*c的值"
description: "按括号优先级计算 (a+b)*c。"
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
source: http://noi.openjudge.cn/ch0103/02/
---

[[TOC]]

### 题意

输入三个整数，计算 $(a+b)c$。

### 思路

代码保留题目中的括号，写成 `(a + b) * c`。不能写成 `a + b * c`，乘法优先会改变表达式含义。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

翻译数学式时保留必要括号，是避免运算优先级错误的最简单方法。
