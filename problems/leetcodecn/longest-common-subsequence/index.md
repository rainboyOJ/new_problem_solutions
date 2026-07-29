---
oj: "leetcodecn"
problem_id: "longest-common-subsequence"
title: "最长公共子序列"
description: "二维 DP：字符相等时 dp[i][j]=dp[i-1][j-1]+1，不等时取 max(dp[i-1][j], dp[i][j-1])。"
difficulty: "普及+/提高"
date: 2026-07-29 12:57
toc: true
tags: ["动态规划", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/longest-common-subsequence/
---

[[TOC]]

### 题意
求两个字符串的最长公共子序列长度。

### 思路
`dp[i][j]` 表示 `text1[0..i-1]` 和 `text2[0..j-1]` 的 LCS 长度。若 `text1[i-1] == text2[j-1]`，则 `dp[i][j] = dp[i-1][j-1] + 1`；否则 `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(mn)$。
- 空间复杂度：$O(mn)$。

### 总结
LCS 是二维 DP 的经典：相等时沿对角线延伸，不等时取上方或左方的较大值。
