---
oj: "roj"
problem_id: "8005"
title: "[NOIP2001 普及组] 数的计算(改)"
description: "设 f[i] 为首项是 i 的合法数列个数，递推 f[i]=1+s[i/2]，s 为前缀和，对 100000 取模。"
difficulty: "入门"
date: 2026-10-02 16:22
updated: 2026-10-06 16:43
toc: true
tags: ["动态规划", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8005
---

[[TOC]]

## 题目描述

给定正整数 $n$。合法数列定义：仅含 $n$ 的数列合法；在合法数列末尾追加一个正整数 $y$，要求 $y$ 不超过末项的一半，得到的新数列仍合法。求合法数列总数，结果只保留最低 $5$ 位（不足 $5$ 位直接输出）。$1 \leqslant n \leqslant 10^5$。

输入一行一个整数 $n$；输出一行一个整数表示答案。

样例输入：`6`，样例输出：`6`。

## 思路

设 $f(i)$ 表示首项为 $i$ 的合法数列个数，则 $f(i)=1+\sum_{j=1}^{\lfloor i/2\rfloor}f(j)$，其中 $1$ 对应数列 $[i]$ 自身。用前缀和 $s(i)=s(i-1)+f(i)$ 把求和变成 $s(\lfloor i/2\rfloor)$，递推即可。答案对 $100000$ 取模。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
