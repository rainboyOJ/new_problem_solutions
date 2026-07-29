---
oj: "leetcodecn"
problem_id: "edit-distance"
title: "编辑距离"
description: "二维 DP：插入、删除、替换分别对应三个相邻状态转移，取最小值。"
difficulty: "提高+/省选-"
date: 2026-07-29 12:58
toc: true
tags: ["动态规划", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/edit-distance/
---

[[TOC]]

### 题意
求两个字符串之间的最小编辑距离（插入、删除、替换）。

### 思路
`dp[i][j]` 表示 `word1[0..i-1]` 变成 `word2[0..j-1]` 的最少操作数。若 `word1[i-1] == word2[j-1]`，则 `dp[i][j] = dp[i-1][j-1]`；否则 `dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])`，分别对应删除、插入、替换。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(mn)$。
- 空间复杂度：$O(mn)$。

### 总结
编辑距离的三个操作对应三个相邻状态：删除从 `dp[i-1][j]` 转移，插入从 `dp[i][j-1]` 转移，替换从 `dp[i-1][j-1]` 转移。
