---
oj: "roj"
problem_id: "2027"
title: "usaco-2.2.2 集合"
description: "将连续整数集合二等分转化为0-1背包计数DP，最后利用对称性除以2统计无序划分数。"
difficulty: "普及-"
date: 2026-10-01 03:32
updated: 2026-10-06 09:51
toc: true
tags:
  - 动态规划
  - 背包问题
  - 计数DP
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2027
---

[[TOC]]

## 题目描述

给定正整数 $N$，把集合 $\{1,2,\dots,N\}$ 划分成两个子集，要求两个子集的数字和相等（交换两个集合算同一种方案），求划分方案总数，不存在则输出 $0$。例如 $N=7$ 时有 4 种，如 $\{1,6,7\}$ 与 $\{2,3,4,5\}$。输入一行一个整数 $N$；样例输入 `7`，样例输出 `4`。

## 思路

总和 $S=\frac{N(N+1)}{2}$ 为奇数时无解输出 0；否则用 0-1 背包计数求从 $1..N$ 中选数使和为 $S/2$ 的方案数：$dp[j]$ 表示和为 $j$ 的取法数，逐个加入数字 $i$ 并倒序转移 $dp[j] \leftarrow dp[j]+dp[j-i]$。每个无序划分在 $dp[S/2]$ 中被统计两次（选中的集合可以是两半中任意一个），最终答案为 $dp[S/2]/2$。

## 参考代码

@include-code(./main.cpp, cpp)

