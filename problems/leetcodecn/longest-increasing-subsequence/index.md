---
oj: "leetcodecn"
problem_id: "longest-increasing-subsequence"
title: "最长递增子序列"
description: "贪心+二分：tails 数组维护各长度子序列的最小结尾，lower_bound 更新保证严格递增。"
difficulty: "普及+/提高"
date: 2026-07-29 12:45
toc: true
tags: ["动态规划", "二分查找", "贪心"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/longest-increasing-subsequence/
---

[[TOC]]

### 题意
求数组的最长严格递增子序列长度。

### 思路
维护 `tails` 数组：`tails[k]` 表示长度为 `k+1` 的递增子序列的最小结尾元素。对每个 `x`，用 `lower_bound` 找到 `tails` 中第一个 $\geqslant x$ 的位置并替换；若 `x` 大于所有 `tails`，则追加。

严格递增用 `lower_bound`（$\geqslant$），非严格递增用 `upper_bound`（$>$）。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \log n)$。
- 空间复杂度：$O(n)$。

### 总结
LIS 的 $O(n \log n)$ 解法：`tails` 数组维护的是"各长度最优结尾"，`lower_bound` 更新保证严格递增。`tails` 的长度即为答案，但 `tails` 本身不一定是合法的子序列。
