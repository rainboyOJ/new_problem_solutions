---
oj: "roj"
problem_id: "1287"
title: "最低通行费"
description: "时限 2N-1 恰等于右下路径的格子数，路径只能向右或向下，退化为经典二维网格 DP，滚动数组 O(N^2) 求最小费用。"
difficulty: "普及-"
date: 2026-09-30 03:26
updated: 2026-10-05 08:02
toc: true
tags:
  - 动态规划
  - 网格DP
  - 滚动数组
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1287
---

[[TOC]]

## 题目描述

$N \times N$ 的费用网格（$1 \leqslant N < 100$，格子费用 $\leqslant 100$），从左上角走到右下角，每经过一个格子花 1 单位时间并缴纳该格费用，总时间不得超过 $2N-1$，只能上下左右移动且不能离开网格。输入第一行 $N$，随后 $N$ 行每行 $N$ 个整数；输出最少总费用（含起点与终点）。样例输入 `5` 及费用矩阵 `1 4 6 8 10 / 2 5 7 15 17 / 6 8 9 18 20 / 10 11 12 19 21 / 20 23 25 29 33`，输出 `109`。

## 思路

从 $(1,1)$ 到 $(N,N)$ 最少要走 $2N-2$ 步、经过 $2N-1$ 个格子，恰好等于时限，所以路径只能向右或向下。设 $dp[j]$ 为走到当前行第 $j$ 列的最小累计费用，DP 转移为 $dp[j]=\min(\text{上方},\text{左方})+a[i][j]$，滚动更新一行，答案即 $dp[N]$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
