---
oj: "noi_openjudge"
problem_id: "ch0103-19"
title: "A*B问题"
description: "读取两个整数并输出乘积。"
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
source: http://noi.openjudge.cn/ch0103/19/
---

[[TOC]]

### 题意

输入两个整数，输出它们的乘积。

### 思路

解包读入两个数，使用 `a * b` 计算。Python 整数会自动扩展精度，题面范围内无需考虑溢出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

基础算术题的重点是准确读取数据类型和输出格式。
