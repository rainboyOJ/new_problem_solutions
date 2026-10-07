---
oj: "roj"
problem_id: "2055"
title: "家的范围"
description: "以每格为右下角的最大全 1 正方形边长做二维 DP，f[r][c]=min(上、左、左上)+1，再按边长分桶后缀和统计每个尺寸的正方形个数。"
difficulty: "普及-"
date: 2026-10-01 05:19
updated: 2026-10-06 10:29
toc: true
tags:
  - "dp"
  - "递推"
  - "二维网格"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2055
---

[[TOC]]

## 题目描述

给定一个 $N\times N$（$2\leqslant N\leqslant 250$）的 0/1 字符矩阵，`1` 表示完好、`0` 表示被毁坏。求所有边长 $k\geqslant 2$、内部不含 `0` 的正方形子区域个数（可重叠），按 $k$ 从小到大输出每个确实存在的尺寸及个数。

输入：第一行 $N$，接下来 $N$ 行每行 $N$ 个无空格字符。样例输入 `6` / `101111` / `001111` / `111111` / `001111` / `101101` / `111001`，输出 `2 10` / `3 4` / `4 1`。

## 思路

设 $f[r][c]$ 为以 $(r,c)$ 为右下角的最大全 1 正方形边长，格子为 `0` 时 $f=0$，否则 $f[r][c]=\min(f[r-1][c-1],f[r-1][c],f[r][c-1])+1$。若 $f[r][c]=L$，该格向边长 $1\sim L$ 的尺寸各贡献一个正方形；按 $L$ 分桶后从大到小做一遍后缀和，即得每个存在尺寸的总数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
