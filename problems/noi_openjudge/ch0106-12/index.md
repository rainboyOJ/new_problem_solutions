---
oj: "noi_openjudge"
problem_id: "ch0106-12"
title: "计算2的N次方"
description: "使用 Python 的幂运算和任意精度整数计算 2 的 N 次方。"
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
source: http://noi.openjudge.cn/ch0106/12/
---

[[TOC]]

### 题意

输出 $2^N$，其中 $N\leqslant100$。

### 思路

`2**exponent` 是 Python 的整数幂运算。结果即使超过固定长度整数范围，Python 也会自动使用任意精度表示。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

结果有 $O(N)$ 位，计算和输出的复杂度受结果位数限制。

### 总结

幂运算的 Python 写法是 `**`，不要把 `^` 误认为乘方。
