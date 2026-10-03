---
oj: "leetcodecn"
problem_id: "perfect-squares"
title: "完全平方数"
description: "完全背包 DP：dp[i] 从所有不超过 i 的平方数转移，取最小值。"
difficulty: "普及/提高-"
date: 2026-07-29 12:37
updated: 2026-10-03 12:38
toc: true
tags: ["动态规划", "完全背包"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "luogu"
    problem_id: "U663703"
    reason: "B 的 dp[i]=min(dp[i-j*j]+1) 就是在 A 教的正序完全背包转移 dp[c]=dp[c]||dp[c-v] 上把物品换成所有平方数、把可达性判定换成取最少件数，无限件这一关键设定被完整复用。"
  - oj: "luogu"
    problem_id: "P1616"
    reason: "B 的 main.cpp（dp[i]=min(dp[i],dp[i-j*j]+1)）直接复用 A 教的一维完全背包状态设计与「容量正序、让本轮更新后的状态继续参与转移」这一无限次复用步骤，只是把物品集合换成平方数、把取 max 价值换成取 min 项数并把初值改为 INF，Δrank=2 属台阶题而非新范式。"
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
