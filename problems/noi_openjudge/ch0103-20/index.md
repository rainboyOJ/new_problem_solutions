---
oj: "noi_openjudge"
problem_id: "ch0103-20"
title: "计算2的幂"
description: "使用左移 1<<n 直接计算 2 的 n 次方。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/20/
---

[[TOC]]

### 题意

输入非负整数 $n$，计算 $2^n$。

### 思路

二进制中 `1 << n` 是把二进制的 `1` 左移 $n$ 位，数值恰为 $2^n$。题目限制 $n<31$，当然也可写 `2 ** n`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

在题目给定范围内，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

二的幂与位移一一对应；`1 << n` 是竞赛代码中简洁且精确的写法。
