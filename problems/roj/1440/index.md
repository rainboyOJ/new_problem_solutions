---
oj: "roj"
problem_id: "1440"
title: "「一本通 1.3 例 1」数的划分"
description: "整数划分计数 DP：设 f[i][j] 为 i 拆成 j 个不减正整数之和的方案数，按末份是否为 1 转移，O(nk) 递推。"
difficulty: "入门"
date: 2026-09-30 10:33
updated: 2026-10-05 23:48
toc: true
tags:
  - "动态规划"
  - "计数DP"
  - "整数划分"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1440
---

[[TOC]]

## 题目描述

给定两个整数 $n, k$，把 $n$ 拆成恰好 $k$ 个正整数之和，同一种拆法改变顺序只算一次。

例如 $n=7, k=3$ 时答案为 $4$：$1,1,5$；$1,2,4$；$1,3,3$；$2,2,3$。

## 思路

为避免重复，约定每份按不减顺序排列。设 $f[i][j]$ 表示把 $i$ 拆成 $j$ 个不减正整数之和的方案数：末份为 $1$ 时去掉它，对应 $f[i-1][j-1]$；末份至少为 $2$ 时每份都减 $1$，对应 $f[i-j][j]$。转移方程为 $f[i][j] = f[i-1][j-1] + f[i-j][j]$，答案即 $f[n][k]$。

## 参考代码

@include-code(./main.cpp, cpp)
