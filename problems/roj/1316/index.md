---
oj: "roj"
problem_id: "1316"
title: "【例4.6】数的计数(Noip2001)"
description: "设 f(i) 为 i 能生成的数的个数，由 f(i)=1+Σf(x) 差分得 f(i)=f(i-1)+[i 偶]·f(i/2)，顺序递推求 f(n)。"
difficulty: "普及-"
date: 2026-09-30 04:54
updated: 2026-10-05 09:11
toc: true
tags: ["递推", "动态规划", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1316
---

[[TOC]]

## 题目描述

输入自然数 $n$（$n \leqslant 1000$）。可以反复在 $n$ 的左边添写一个不超过当前最左边那个数一半的自然数，直到不能再添为止；问包括 $n$ 本身在内一共能得到多少个数。输入一行 $n$，输出个数。样例输入 `6`，输出 `6`，对应 $6, 16, 26, 126, 36, 136$。

## 思路

设 $f(i)$ 表示从 $i$ 出发能生成的数的个数（含 $i$ 本身），则左边可补 $x \in [1, \lfloor i/2 \rfloor]$，即 $f(i) = 1 + \sum_{x=1}^{\lfloor i/2 \rfloor} f(x)$。把相邻两式相减，求和被消掉，得到 $f(i) = f(i-1)$（$i$ 为奇数）或 $f(i) = f(i-1) + f(i/2)$（$i$ 为偶数），边界 $f(0) = f(1) = 1$；从 $2$ 到 $n$ 顺序递推，时间 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
