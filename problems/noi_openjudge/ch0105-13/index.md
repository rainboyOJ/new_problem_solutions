---
oj: "noi_openjudge"
problem_id: "ch0105-13"
title: "乘方计算"
description: "使用内建 pow 计算整数 a 的 n 次方。"
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
source: http://noi.openjudge.cn/ch0105/13/
---

[[TOC]]

### 题意

计算整数 $a^n$，题面保证结果范围安全。

### 思路

`pow(base, exponent)` 是 Python 的整数乘方内建函数，与 `base ** exponent` 等价。它比手写循环反复乘更直接。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

内建整数幂使用高效算法；在本题范围下可视为 $O(\log n)$ 次大整数乘法。

### 总结

固定底数的整数幂优先使用 `pow` 或 `**`，无需手写循环。
