---
oj: "roj"
problem_id: "1098"
title: "质因数分解"
description: "n 是两个不同质数之积，从小到大试除到 sqrt(n) 找最小质因子 p，输出 n/p 即较大质数，O(sqrt(n))。"
difficulty: "入门"
date: 2026-09-29 18:39
updated: 2026-10-05 01:00
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1098
---

[[TOC]]

## 题目描述

已知正整数 $n$ 是两个**不同**质数的乘积（$6 \le n \le 2 \times 10^9$），求较大的那个质数。输入一行一个 $n$，输出一行较大的质数。样例输入 `21`，输出 `7`（$21 = 3 \times 7$）。

## 思路

设 $n = p \cdot q$ 且 $p < q$，则必有 $p < \sqrt{n}$：否则 $p, q$ 都大于 $\sqrt{n}$，乘积会超过 $n$。于是从小到大枚举 $d = 2, 3, \dots, \lfloor\sqrt{n}\rfloor$，第一个整除 $n$ 的 $d$ 就是较小的质数 $p$（若 $d$ 是合数，它必有更小的因子也整除 $n$，与“第一个”矛盾），输出 $n / p$ 即可，复杂度 $O(\sqrt{n})$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
