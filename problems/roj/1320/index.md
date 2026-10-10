---
oj: "roj"
problem_id: "1320"
title: "【例6.2】均分纸牌(Noip2002)"
description: "把每堆纸牌数减去平均值得到偏差，再求偏差的前缀和；每一条前缀和非零的相邻边界至少要搬一次，且各搬一次即可做到，答案就是非零前缀和的个数。"
difficulty: "普及-"
date: 2026-09-30 05:05
updated: 2026-10-05 09:18
toc: true
tags: [贪心, 前缀和]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1320
---

[[TOC]]

## 题目描述

有 $n$ 堆纸牌，第 $i$ 堆有 $a_i$ 张，总数保证是 $n$ 的倍数。每次可以从一堆取若干张移到相邻的一堆（第 $1$ 堆只能移给第 $2$ 堆，第 $n$ 堆只能移给第 $n-1$ 堆）。输入 $n$ 和 $a_1 \ldots a_n$（$1 \leqslant n \leqslant 100$，$1 \leqslant a_i \leqslant 10000$），输出使每堆牌数都相等的最少移动次数。样例：输入 `4` / `9 8 17 6`，输出 `3`。

## 思路

设平均值 $\bar a$，第 $i$ 堆的偏差 $d_i = a_i - \bar a$。跨过第 $i$ 条边界（$i \to i+1$）的净牌数被两端盈亏唯一确定，恰好等于前缀和 $s_i = d_1 + \cdots + d_i$，所以 $s_i \ne 0$ 时这条边界至少要搬一次，而每条非零边界各搬一次就可以做到（把同号的区间接力推平），因此答案是 $s_1, \ldots, s_{n-1}$ 中非零的个数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
