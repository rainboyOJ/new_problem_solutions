---
oj: "leetcodecn"
problem_id: "maximum-subarray"
title: "最大子数组和"
description: "Kadane 算法：以 i 结尾的最大和 = max(a[i], dp[i-1] + a[i])，滚动 O(1) 空间。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "动态规划", "分治", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/maximum-subarray/
---

[[TOC]]

### 题意

整数数组 nums，找出和最大的连续子数组，返回其和。

### 思路

暴力枚举 O(n²)。Kadane 算法：`dp[i]` 表示以 `i` 结尾的子数组最大和，转移 `dp[i] = max(a[i], dp[i-1] + a[i])`。由于只依赖前一个状态，可用一个变量滚动。

全负数组不影响算法正确性，因为每个位置至少可以选自己。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)，一次遍历。
- 空间复杂度：O(1)。

### 总结

Kadane 算法是"线性 DP 滚动"的经典例子。把"枚举所有子数组"降维成"枚举所有结尾位置"，每个结尾只需维护以该位置结尾的最大值。
