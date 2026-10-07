---
oj: "roj"
problem_id: "1267"
title: "【例9.11】01背包问题"
description: "一维滚动 0/1 背包 DP：逐件物品倒序扫描容量，dp[v]=max(dp[v],dp[v-W]+C)，答案为 dp[M]。"
difficulty: "普及-"
date: 2026-09-30 02:38
updated: 2026-10-05 07:39
toc: true
tags: ["动态规划", "背包", "01背包", "python"]
favorite: false
favorite_reason: ""
categories: ["动态规划"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1267
---

[[TOC]]

## 题目描述

一个旅行者有一个最多能装 $M$ 公斤的背包，现在有 $N$ 件物品，第 $i$ 件物品重量为 $W_i$、价值为 $C_i$，每件物品最多选一次，求能获得的最大总价值。
**输入**：第一行两个整数 $M$（背包容量，$M \leqslant 200$）和 $N$（物品数量，$N \leqslant 30$）；接下来 $N$ 行每行两个整数 $W_i, C_i$，表示每件物品的重量和价值。**输出**：仅一行，一个数，表示最大总价值。
**样例输入**：`10 4`，`2 1`，`3 3`，`4 5`，`7 9`（每行一项）；**样例输出**：`12`（选物品 2 和 4，重量 $3+7=10$，价值 $3+9=12$）

## 思路

一维 0/1 背包：$dp[v]$ 表示容量不超过 $v$ 时的最大价值，逐件物品转移 $dp[v] = \max(dp[v], dp[v-W_i]+C_i)$，答案为 $dp[M]$。内层容量必须倒序扫描，这样 $dp[v-W_i]$ 读到的还是没考虑本物品的旧值，保证每件物品最多选一次（正序就变成完全背包）。$dp$ 全初始化为 $0$ 即可，因为"一件不拿"总是合法方案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
