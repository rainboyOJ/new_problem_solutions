---
oj: "noi_openjudge"
problem_id: "ch0103-01"
title: "A+B问题"
description: "读取两个整数并直接输出它们的和。"
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
source: http://noi.openjudge.cn/ch0103/01/
---

[[TOC]]

### 题意

输入两个整数，输出它们的和。

### 思路

用 `map(int, input().split())` 同时读入两个整数，`+` 得到答案。Python 整数没有固定 32 位上限，但题面保证结果在 C/C++ 整型范围内。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

固定数量的整数可直接解包，变量名与题面一一对应。
