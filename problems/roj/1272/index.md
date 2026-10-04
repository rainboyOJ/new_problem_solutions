---
oj: "roj"
problem_id: "1272"
title: "【例9.16】分组背包"
description: "外层枚举组、容量倒序、内层枚举组内物品，容量倒序保证每轮只读上一组的旧值，同组物品不会叠加。"
difficulty: "普及-"
date: 2026-09-30 02:50
updated: 2026-10-05 07:44
toc: true
tags: ["动态规划", "背包", "分组背包"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1272
---

[[TOC]]

## 题目描述

一个最多能装 $V$（$V \leqslant 200$）公斤的背包，$N$（$N \leqslant 30$）件物品重量 $W_i$、价值 $C_i$，划分为 $T$（$T \leqslant 10$）组，每组最多选一件。第一行输入 $V, N, T$，随后 $N$ 行每行 $W_i, C_i, P$（重量、价值、组号）；输出一行，为最大总价值。如样例输入 `10 6 3 / 2 1 1 / 3 3 1 / 4 8 2 / 6 9 2 / 2 8 3 / 3 9 3`，输出 `20`（选 $(3,3)$、$(4,8)$、$(3,9)$）。

## 思路

设 $dp[cap]$ 为容量不超过 $cap$ 的最大价值，三层循环：外层枚举组、容量倒序、内层枚举组内物品做 $dp[cap] = \max(dp[cap], dp[cap-W_j]+C_j)$。容量倒序让每个格子只读上一组的旧值，同组物品不会叠加，天然满足每组最多选一件；$dp[cap]$ 单调不减，答案即 $dp[V]$。

## 参考代码

@include-code(./main.cpp, cpp)
