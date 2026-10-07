---
oj: "roj"
problem_id: "1652"
title: "「一本通 6.6 练习 1」牡牛和牝牛"
description: "线性 DP 计数：按前缀末位性别转移，以牝牛结尾等于总方案数，以牡牛结尾回看 K+1 位之前的总方案数，O(N) 递推取模。"
difficulty: "普及-"
date: 2026-10-01 00:09
updated: 2026-10-06 01:41
toc: true
tags: ["动态规划", "计数DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1652
---

[[TOC]]

## 题目描述

$N$ 只牛（牡牛/牝牛相同）排队，任意两只牡牛之间至少 $K$ 只牝牛，求合法方案数对 $5000011$ 取模（$1 \le N \le 10^5$，$0 \le K < N$）。

## 思路

设 $s_i$ 为长度 $i$ 的方案数：末位放牝牛贡献 $s_{i-1}$，放牡牛时若 $i \le K$ 贡献 1、否则贡献 $s_{i-K-1}$，两者相加取模，答案为 $s_N$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
