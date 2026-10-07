---
oj: "roj"
problem_id: "3591"
title: "[NOIP2011-提高] 计算系数"
description: "二项式定理得 x^n y^m 项系数为 C(k,n)a^n b^m，杨辉三角递推组合数加快速幂取模 10007"
difficulty: "普及"
date: 2026-10-02 09:27
updated: 2026-10-06 14:42
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3591
---

[[TOC]]

## 题目描述

给定整数 $a, b, k, n, m$（保证 $n + m = k$），求多项式 $(by+ax)^k$ 展开后 $x^n y^m$ 项的系数，对 $10007$ 取模。输入一行五个整数；输出一个整数。样例：`1 1 3 1 2` → `3`。数据范围：$0 \le k \le 1000$，$0 \le n, m \le k$，$0 \le a, b \le 10^6$。

## 思路

由二项式定理，$x^n y^m$ 的系数为 $\binom{k}{n} a^n b^m$。用杨辉三角递推求 $\binom{k}{n} \bmod 10007$（$k \le 1000$，$O(k^2)$），$a^n, b^m$ 用快速幂取模；全程不出现除法，$a$ 或 $b$ 为 $0$ 时结果自然为 $0$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
