---
oj: "noi_openjudge"
problem_id: "ch0106-14"
title: "求10000以内n的阶乘"
description: "调用 math.factorial 计算 10000 以内的阶乘，并兼容大整数输出限制。"
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
source: http://noi.openjudge.cn/ch0106/14/
---

[[TOC]]

### 题意

输出 $n!$，其中 $0\leqslant n\leqslant10000$。

### 思路

`math.factorial(number)` 用 Python 任意精度整数计算阶乘。Python 3.11 及更高版本默认限制极长整数转为字符串的位数，代码在该接口存在时调用 `set_int_max_str_digits(0)`，使 $10000!$ 可以完整输出；Python 3.10 没有该接口，会自动跳过。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

输出本身需要与 $n!$ 的十进制位数成正比的时间和空间。

### 总结

当结果极长时，除了计算本身，也要注意运行时对大整数输出的安全限制。
