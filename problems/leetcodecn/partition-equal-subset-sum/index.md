---
oj: "leetcodecn"
problem_id: "partition-equal-subset-sum"
title: "分割等和子集"
description: "0/1 背包判断能否凑满 sum/2，倒序更新避免重复使用元素。"
difficulty: "普及+/提高"
date: 2026-07-29 12:47
toc: true
tags: ["动态规划", "0/1背包"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/partition-equal-subset-sum/
---

[[TOC]]

### 题意
判断数组能否分成两个和相等的子集。

### 思路
若总和为奇数，不可能。否则目标为 `sum/2`，转化为 0/1 背包：从 `nums` 中选若干数，和恰好为 `target`。`dp[i]` 表示和 `i` 是否可达，倒序更新避免重复使用同一元素。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \cdot \text{target})$。
- 空间复杂度：$O(\text{target})$。

### 总结
分割等和子集是 0/1 背包的判定版本。倒序更新是关键：正序更新会导致同一元素被多次选取。
