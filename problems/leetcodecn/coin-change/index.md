---
oj: "leetcodecn"
problem_id: "coin-change"
title: "零钱兑换"
description: "完全背包 DP：dp[i] 从所有硬币面额转移，取最小值，不可达用哨兵标记。"
difficulty: "普及+/提高"
date: 2026-07-29 12:38
toc: true
tags: ["动态规划", "完全背包"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/coin-change/
---

[[TOC]]

### 题意
给定硬币面额和金额，求最少硬币数。每种硬币无限使用。

### 思路
`dp[i]` 表示凑成金额 `i` 的最少硬币数。`dp[i] = min(dp[i-c] + 1)` 对所有 `c <= i`。初值 `dp[0] = 0`，其余 `amount + 1`（不可达哨兵）。最终 `dp[amount] > amount` 则无解。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \cdot \text{amount})$。
- 空间复杂度：$O(\text{amount})$。

### 总结
零钱兑换是完全背包求最少物品数的经典题。不可达哨兵用 `amount + 1`（而非 `INF`），因为最多用 `amount` 个 1 元硬币。
