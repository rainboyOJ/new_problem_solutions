---
oj: "leetcodecn"
problem_id: "unique-paths"
title: "不同路径"
description: "网格 DP：首行首列初始化为 1，内部 dp[j] += dp[j-1] 即上方加左方。"
difficulty: "普及-"
date: 2026-07-29 12:49
toc: true
tags: ["动态规划", "组合数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/unique-paths/
---

[[TOC]]

### 题意
从左上到右下，只能向右或向下，求路径数。

### 思路
`dp[j]` 表示到达当前行第 `j` 列的路径数。首行全为 1，每行从左到右 `dp[j] += dp[j-1]`（上方 + 左方）。空间优化到一维。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(mn)$。
- 空间复杂度：$O(n)$。

### 总结
网格路径计数是二维 DP 的入门题。首行首列初始化为 1，转移方程 `dp[i][j] = dp[i-1][j] + dp[i][j-1]`，空间可优化到一维。
