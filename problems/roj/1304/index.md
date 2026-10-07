---
oj: "roj"
problem_id: "1304"
title: "数的划分"
description: "把 n 拆成 k 个正整数且不计顺序，按「最小值是否为 1」分类得到 p_k(n)=p_{k-1}(n-1)+p_k(n-k)，递推 O(nk) 求解。"
difficulty: "普及-"
date: 2026-09-30 04:05
updated: 2026-10-05 08:50
toc: true
tags: ["递推", "数学", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1304
---

[[TOC]]

## 题目描述

把整数 $n$ 分成 $k$ 份，每份不能为空，任意两份不能相同（不考虑顺序），例如 $n=7$、$k=3$ 时 `1,1,5`、`1,5,1`、`5,1,1` 算同一种。输入一行两个整数 $n, k$（$6 < n \leqslant 200$，$2 \leqslant k \leqslant 6$），输出不同的分法总数。样例输入 `7 3` 对应输出 `4`：`1,1,5`；`1,2,4`；`1,3,3`；`2,2,3`。

## 思路

设 $f[i][j]$ 为把 $i$ 拆成 $j$ 个正整数、不计顺序的方案数，按最小值是否为 $1$ 分类：最小值为 $1$ 时删掉一个 $1$ 得 $f[i-1][j-1]$，最小值 $\geqslant 2$ 时每份减 $1$ 得 $f[i-j][j]$，两类不重不漏，故 $f[i][j] = f[i-1][j-1] + f[i-j][j]$。边界：$j=1$ 时只有 $1$ 种，$i<j$ 时为 $0$；状态 $O(nk)$、转移 $O(1)$，递推即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
