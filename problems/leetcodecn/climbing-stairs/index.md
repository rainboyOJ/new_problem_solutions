---
oj: "leetcodecn"
problem_id: "climbing-stairs"
title: "爬楼梯"
description: "Fibonacci 型递推：dp[i] = dp[i-1] + dp[i-2]，初值 dp[1]=1, dp[2]=2。"
difficulty: "入门"
date: 2026-07-29 12:29
toc: true
tags: ["动态规划", "递推"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/climbing-stairs/
---

[[TOC]]

### 题意
爬 n 阶楼梯，每次可走 1 或 2 步，求方法数。

### 思路
到达第 `i` 阶的方法数 = 从第 `i-1` 阶走 1 步 + 从第 `i-2` 阶走 2 步，即 `dp[i] = dp[i-1] + dp[i-2]`。初值 `dp[1] = 1`，`dp[2] = 2`。

这是 Fibonacci 数列的平移形式。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$，只需前两个值。

### 总结
爬楼梯是动态规划入门题：状态定义、转移方程、初值三者缺一不可。`dp[i] = dp[i-1] + dp[i-2]` 是 Fibonacci 型递推，空间可优化到 $O(1)$。
