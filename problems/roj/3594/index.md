---
oj: "roj"
problem_id: "3594"
title: "[NOIP2012-普及] 质因数分解"
description: "n 是两个不同质数之积，从小到大试除到 √n 时第一个命中的因数就是较小质因数，直接输出商即较大的质因数。"
difficulty: "普及-"
date: 2026-10-02 09:40
updated: 2026-10-06 14:54
toc: true
tags: ["数论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3594
---

[[TOC]]

## 题目描述

已知正整数 $n$ 是两个**不同**质数的乘积，试求出两者中较大的那个质数。
输入一个正整数 $n$（$n \leqslant 2 \times 10^9$），输出较大的那个质数 $p$。
样例：输入 `21`（$= 3 \times 7$），输出 `7`。

## 思路

设 $n = p \cdot q$（$p < q$），则 $p < \sqrt n < q$：从小到大试除，第一个能整除 $n$ 的 $d$ 就是最小质因数 $p$，直接输出商 $n / d$ 即答案。试除上界用 $d \cdot d \leqslant n$ 判断，最多约 44722 次，$O(\sqrt n)$ 足够通过。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
