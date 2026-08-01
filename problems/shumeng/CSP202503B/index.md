---
oj: "shumeng"
problem_id: "CSP202503B"
title: "机器人饲养指南"
description: "用完全背包式 DP 枚举最后一天投喂的苹果数，求恰好投喂 n 个苹果的最大收益。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["动态规划", "完全背包"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503B
---

[[TOC]]

### 题意

每天最多投喂 `m` 个苹果，投喂 `i` 个的快乐值是 `A[i]`。把全部 `n` 个苹果分成若干天投喂，求最大快乐值。

### 思路

设 `dp[i]` 表示恰好投喂 `i` 个苹果时的最大收益。若最后一天投喂 `j` 个苹果，则前面投喂了 `i-j` 个，转移为 `dp[i]=max(dp[i],dp[i-j]+A[j])`，其中 `1<=j<=min(m,i)`。

小数据可以直接递归枚举每天投喂数量：

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 `O(nm)`，空间复杂度为 `O(n)`。

### 总结

每天的收益不要求单调，因此不能只选择收益最大的投喂数量；按最后一天划分状态可以完整枚举所有合法分组。
