---
oj: "roj"
problem_id: "1648"
title: "「一本通 6.6 例 1」计算系数"
description: "二项式定理一步到位：x^n y^m 项系数 = C(k,n)·a^n·b^m mod 10007，组合数 + 快速幂即可。"
difficulty: "入门"
date: 2026-09-30 23:55
updated: 2026-10-06 01:38
toc: true
tags: ["数学", "二项式定理", "快速幂", "组合数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1648
---

[[TOC]]

## 题目描述

给定整数 $a,b,k,n,m$（$0\le n,m\le k$ 且 $n+m=k$，$0\le a,b\le 10^6$），求多项式 $(ax+by)^k$ 展开后 $x^ny^m$ 项的系数，结果对 $10007$ 取模。

输入一行 5 个整数 $a,b,k,n,m$；输出一行一个整数，即所求系数模 $10007$ 的值。

样例输入 `1 1 3 1 2` 时，$(x+y)^3=x^3+3x^2y+3xy^2+y^3$，$xy^2$ 项系数为 $3$，样例输出 `3`。

## 思路

由二项式定理，$(ax+by)^k$ 展开后 $x^n y^m$ 项（$m=k-n$）的系数唯一为 $\binom{k}{n}\cdot a^n\cdot b^m$。$k\le 1000$，用杨辉三角递推 $O(k^2)$ 求出 $\binom{k}{n}$，$a^n$、$b^m$ 用快速幂，全程对 $10007$ 取模即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
