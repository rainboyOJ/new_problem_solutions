---
oj: "luogu"
problem_id: "P3959"
title: "[NOIP 2017 提高组] 宝藏"
description: "按挖掘深度分层做子集 DP，预处理新节点连接已挖集合的最短边代价。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["状态压缩DP", "子集枚举", "分层", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3959
---

[[TOC]]

### 题意

任选一个根免费打通，其他点通过边接入。连接到深度 `d-1` 父点的边代价乘 `d`，求挖完所有点的最小总代价。

### 思路

`dp[mask]` 表示前若干层已经挖出 `mask` 的最小代价。第 `depth` 层选择补集的一个非空子集加入；每个新点连接到已挖集合中边权最小的点，贡献再乘当前深度。

先预处理 `connection[v][mask]`。对每个基础 `mask`，递归枚举补集子集并累计连接边权，所有基础集合的枚举总量是 $3^n$，比逐一扫描全部 `2^n` 子集的 $4^n$ 常数小很多。

所有单点根状态初值为 0，逐层滚动更新。

### Python 知识

- `bit = mask & -mask` 和 `bit.bit_length()-1` 取得最低集合元素。
- 闭包 `enumerate_additions` 在枚举子集时同步累计费用，避免重复求和。
- `next_dp = dp[:]` 允许某一层不新增节点。

### 代码

@include-code(./main.py, python)

### 复杂度

预处理 $O(n2^n)$，主要转移约 $O(n3^n)$，空间 $O(n2^n+3^n)$；$n\le12$。

### 总结

边费用乘树深度提示“按层加入节点”；`n=12` 则提示用集合表示已挖状态。
