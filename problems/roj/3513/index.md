---
oj: "roj"
problem_id: "3513"
title: "[NOIP2002-普及] 选数"
description: "递增下标 DFS 枚举全部 C(n,k) 个组合去重，对组合和试除到 sqrt(S) 判素（S ≤ 10^8），累加合法组合数。"
difficulty: "普及-"
date: 2026-10-02 04:45
updated: 2026-10-06 12:31
toc: true
tags: ["枚举", "组合", "素数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3513
---

[[TOC]]

## 题目描述

给定 $n$ 个整数 $x_1,\dots,x_n$ 和整数 $k$（$1\le n\le20$，$k<n$，$1\le x_i\le5\times10^6$），任选其中 $k$ 个（不计顺序），求和为素数的选法数。输入第一行 $n,k$，第二行 $x_1,\dots,x_n$；输出满足条件的种数。
样例输入 `4 3` / `3 7 12 19`，样例输出 `1`（仅 $3+7+19=29$ 为素数）。

## 思路

递增下标 DFS 枚举全部 $\binom{n}{k}$ 个组合天然不重不漏，每个组合求和后试除到 $\sqrt S$ 判素（$S\le10^8$），累加合法组合数即可。

## 参考代码

@include-code(./main.cpp, cpp)
