---
oj: "roj"
problem_id: "2085"
title: "巨大的牛棚"
description: "经典网格 DP：定义 dp[r][c] 为以 (r,c) 为右下角的全空最大正方形边长，由上方、左方、左上三方取 min 加一，O(N²) 求出答案。"
difficulty: "普及"
date: 2026-10-01 07:45
updated: 2026-10-06 10:44
toc: true
tags: ["动态规划", "网格 DP", "二维悬线"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2085
---

[[TOC]]

## 题目描述

给定一个 $N \times N$ 网格和 $T$ 个有树格子的坐标，求能建在空地上的正方形牛棚的最大边长。$1 \le N \le 1000$，$1 \le T \le 10000$。

## 思路

设 $dp[r][c]$ 为以 $(r,c)$ 为右下角的全空正方形最大边长。若该格有树则 $dp[r][c]=0$；否则它由上方、左方、左上方三个相邻正方形共同决定，转移式为 $dp[r][c]=\min(dp[r-1][c],dp[r][c-1],dp[r-1][c-1])+1$。遍历网格取最大值即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
