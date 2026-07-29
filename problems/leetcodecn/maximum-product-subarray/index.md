---
oj: "leetcodecn"
problem_id: "maximum-product-subarray"
title: "乘积最大子数组"
description: "同时维护以当前位置结尾的最大和最小乘积，负数交换两者，取全局最大。"
difficulty: "普及+/提高"
date: 2026-07-29 12:46
toc: true
tags: ["动态规划"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/maximum-product-subarray/
---

[[TOC]]

### 题意
求数组中乘积最大的连续子数组。

### 思路
同时维护以当前位置结尾的最大乘积 `mx` 和最小乘积 `mn`。遇到负数时 `mx` 和 `mn` 交换（因为负数使最大变最小、最小变最大），然后正常更新：`mx = max(x, mx*x)`, `mn = min(x, mn*x)`。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
乘积子数组的关键是负数会交换最大最小贡献，因此必须同时维护两者。这与最大子数组和不同：加法不会翻转符号。
