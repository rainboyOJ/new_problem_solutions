---
oj: "roj"
problem_id: "1259"
title: "【例9.3】求最长不下降序列"
description: "用 f[i] 表示以第 i 个数结尾的最长不下降子序列长度，枚举前面更小的 j 转移，O(n²) 求出最大长度。"
difficulty: "普及-"
date: 2026-09-30 02:21
updated: 2026-10-05 07:20
toc: true
tags: ["动态规划", "最长上升子序列", "线性DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1259
---

[[TOC]]

## 题目描述

给定 $n(1 \leq n \leq 200)$ 个互不相同整数，求最长不下降子序列长度。输入一行 $n$ 和一行 $n$ 个整数，输出 `max=最大长度`。样例：输入 `14` 与 `13 7 9 16 38 24 37 18 44 19 21 22 63 15`，输出 `max=8`。

## 思路

设 $f_i$ 为以第 $i$ 个数结尾的最长不下降子序列长度。枚举 $j<i$ 且 $b_j \leq b_i$ 的位置，用 $f_j+1$ 更新 $f_i$，答案取 $\max f_i$。$O(n^2)$ 足够。

## 参考代码

@include-code(./main.cpp, cpp)
