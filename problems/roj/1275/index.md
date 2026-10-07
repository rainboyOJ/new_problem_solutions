---
oj: "roj"
problem_id: "1275"
title: "【例9.19】乘积最大"
description: "把长度为 N 的数字串插入 K 个乘号切成 K+1 段使乘积最大。"
difficulty: "普及-"
date: 2026-09-30 02:51
updated: 2026-10-05 07:45
toc: true
tags: ["动态规划", "区间DP", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1275
---

[[TOC]]

## 题目描述

设有长度为 N 的数字串，用 K 个乘号切成 K+1 段（允许前导零），使各段整数乘积最大。第一行 N, K（6 ≤ N ≤ 10，1 ≤ K ≤ 6），第二行数字串；输出最大乘积。

样例：N=4, K=2，串 `1231` → 输出 `62`。

## 思路

区间 DP：设 `dp[i]` 为前 i 位用当前刀数切出的最大乘积，按刀数逐层滚动更新，每层枚举最后一刀位置 t，转移 `dp[i] = max(dp[t] * val(t, i))`，答案为 `dp[N]`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)