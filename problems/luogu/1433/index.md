---
oj: "luogu"
problem_id: "P1433"
title: "吃奶酪"
description: "设 dp[mask][u] 为已经吃掉 mask 中这些奶酪且最后停在 u 的最短路程，做起点固定、终点不限的状压 TSP。"
difficulty: "普及/提高-"
date: 2026-06-21 05:22
toc: true
tags: ["状态压缩", "动态规划", "TSP", "位运算"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1433
---

[[TOC]]

### 题意

平面上有 `n` 块奶酪，小老鼠从原点 `(0,0)` 出发，要把所有奶酪都吃掉。

问最少需要跑多少距离。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

暴力就是直接枚举吃奶酪的顺序，然后把路径长度加起来。

正解是经典状压 TSP。

设：

- `dp[mask][u]` 表示已经吃掉了 `mask` 中这些奶酪，且最后停在第 `u` 块奶酪时的最短距离

预处理两类距离：

- 原点到每块奶酪的距离
- 任意两块奶酪之间的距离

初始化时，直接从原点走到某块奶酪：

- `dp[1<<(i-1)][i] = dist(原点, i)`

然后做标准 TSP 转移：

- 从当前最后一块奶酪 `u`
- 转移到还没吃的奶酪 `v`

最后取所有 `dp[full][i]` 的最小值即可。

注意这里不需要回到原点，所以不再补最后一段回程。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度 $O(n^2 2^n)$，空间复杂度 $O(n 2^n)$。

### 总结

这题是最典型的欧氏 TSP 入门题。
起点固定、终点不限，是它和“回路型 TSP”唯一的区别。
