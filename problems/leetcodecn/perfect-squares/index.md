---
oj: "leetcodecn"
problem_id: "perfect-squares"
title: "完全平方数"
description: "完全背包 DP：dp[i] 从所有不超过 i 的平方数转移，取最小值。"
difficulty: "普及/提高-"
date: 2026-07-29 12:37
toc: true
tags: ["动态规划", "完全背包"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/perfect-squares/
---

[[TOC]]

### 题意
求和为 n 的完全平方数的最少个数。

### 思路
`dp[i]` 表示和为 `i` 的最少完全平方数个数。`dp[i] = min(dp[i - j*j] + 1)` 对所有 `j*j <= i`。初值 `dp[0] = 0`，其余 `INF`。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \sqrt{n})$。
- 空间复杂度：$O(n)$。

### 总结
完全平方数是完全背包的变形：物品是所有平方数，每个可无限使用，求凑满目标的最少物品数。
