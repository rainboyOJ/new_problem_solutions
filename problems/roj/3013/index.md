---
oj: "roj"
problem_id: "3013"
title: "货仓选址"
description: "数轴上到 N 个点的距离和是下凸函数，最小值在中位数取到；排序后把最小与最大配对，每组贡献 B_{N+1-i}-B_i，即 O(N log N)。"
difficulty: "普及-"
date: 2026-10-01 10:13
updated: 2026-10-06 11:13
toc: true
tags: ["贪心", "排序", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3013
---

[[TOC]]

## 题目描述

数轴上有 $N$ 家商店，坐标为 $A_1, A_2, \ldots, A_N$。在数轴上选一家货仓，使货仓到所有商店的距离之和最小，输出这个最小值。

- 输入：第一行整数 $N$，第二行 $N$ 个整数坐标。
- 输出：一个整数，表示最小距离和。
- 数据范围：$1 \le N \le 100\,000$。

样例输入 `4 / 6 2 9 1`，输出 `12`。

## 思路

$d(x)=\sum|x-A_i|$ 是下凸函数，最小值在中位数处取到。把坐标排序后让最小与最大配对，每组贡献 $B_{N+1-i}-B_i$，共 $\lfloor N/2\rfloor$ 组，求和即可。时间复杂度 $O(N\log N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
