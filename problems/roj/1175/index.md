---
oj: "roj"
problem_id: "1175"
title: "除以13"
description: "利用 Python 任意精度整数，直接读入后计算除以 13 的商和余数。"
difficulty: "入门"
date: 2026-09-29 22:02
updated: 2026-09-29 22:05
toc: true
tags:
  - 高精度
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1175
---

[[TOC]]

## 形式化题目

给定一个长度不超过 100 的十进制正整数 $N$，要求输出
$$
q = \left\lfloor \frac{N}{13} \right\rfloor, \quad r = N \bmod 13
$$
其中 $0 \leqslant r < 13$。

## 正解

### 思路

$N$ 最多有 100 位，已经超出普通 64 位整数的范围，必须使用大整数运算。Python 的 `int` 类型天然支持任意精度，因此可以把输入当作一个整数读入，直接利用整数除法 `//` 和取模 `%` 得到商和余数。

这种做法等价于手算竖式除法：从高位到低位逐位把余数“传递”到下一位，即
$$
r_{i} = (10 \cdot r_{i-1} + d_i) \bmod 13
$$
而每一步输出的商位为 $(10 \cdot r_{i-1} + d_i) // 13$。Python 内部对大整数的实现正是按此类算法进行的，所以代码虽然简短，但算法与正解同阶。

### 代码

@include-code(./main.py, python)

### 复杂度

设 $N$ 的十进制长度为 $L$。

- 时间复杂度：$O(L^2)$，来自大整数除法的内部实现（$L \leqslant 100$）。
- 空间复杂度：$O(L)$，用于存储大整数本身。

## 总结

本题是经典的大整数除以单模数问题。Python 凭借任意精度整数，一行读取、两行输出即可完成；核心在于理解题目要求的是整数除法的商和余数，而不是浮点除法。
