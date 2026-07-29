---
oj: "leetcodecn"
problem_id: "minimum-path-sum"
title: "最小路径和"
description: "网格 DP：边界只能来自单方向，内部取上左较小值加上当前格。"
difficulty: "普及-"
date: 2026-07-29 12:55
toc: true
tags: ["动态规划", "网格"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/minimum-path-sum/
---

[[TOC]]

### 题意
网格从左上到右下，只能向右或向下，求最小路径和。

### 思路
`dp[j]` 表示到达当前行第 j 列的最小路径和。首行只累加，内部 `dp[j] = min(dp[j], dp[j-1]) + grid[i][j]`（上方和左方取较小值）。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(mn)$。
- 空间复杂度：$O(n)$。

### 总结
最小路径和与不同路径的转移结构相同，只是把"加法计数"换成"取最小值加权重"。
