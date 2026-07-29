---
oj: "leetcodecn"
problem_id: "house-robber"
title: "打家劫舍"
description: "dp[i] 表示处理到第 i 间时的最大金额，偷当前则跳过前一间，不偷则继承前一间。"
difficulty: "普及-"
date: 2026-07-29 12:36
toc: true
tags: ["动态规划", "递推"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/house-robber/
---

[[TOC]]

### 题意
不能偷相邻房屋，求最大金额。

### 思路
用 `a` 和 `b` 分别表示"不偷当前"和"偷当前"的最大金额。`a = b`（上一轮的偷），`b = max(b, a + nums[i])`（取偷与不偷的较大值）。空间优化到 $O(1)$。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
打家劫舍是线性 DP 的典型：状态只需"前一个"和"前两个"，空间优化到 $O(1)$。
