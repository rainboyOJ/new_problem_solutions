---
oj: "noi_openjudge"
problem_id: "ch0106-11"
title: "大整数减法"
description: "利用 Python 任意精度整数直接完成不超过 200 位的正整数减法。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["高精度", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/11/
---

[[TOC]]

### 题意

给定 $a>b$ 的两个不超过 $200$ 位正整数，输出 $a-b$。

### 思路

Python 的 `int` 不受 C++ 基础整数位数限制，直接读入并相减即可，借位与前导零由运行时处理。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设数字位数为 $d$，时间复杂度和额外空间复杂度均为 $O(d)$。

### 总结

语言自带任意精度时，应把精力放在题目逻辑而不是重复实现借位。
