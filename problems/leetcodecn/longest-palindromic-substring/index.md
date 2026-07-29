---
oj: "leetcodecn"
problem_id: "longest-palindromic-substring"
title: "最长回文子串"
description: "中心扩展：枚举每个中心（奇偶），向两侧扩展直到不回文，记录最长。"
difficulty: "普及+/提高"
date: 2026-07-29 12:56
toc: true
tags: ["字符串", "动态规划"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/longest-palindromic-substring/
---

[[TOC]]

### 题意
求字符串中最长的回文子串。

### 思路
枚举每个中心位置（奇数长度以字符为中心，偶数长度以间隙为中心），向两侧扩展直到不回文，记录最长。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n^2)$。
- 空间复杂度：$O(1)$。

### 总结
中心扩展是最直观的回文子串解法。Manacher 算法可优化到 $O(n)$，但中心扩展对 $n \leqslant 1000$ 足够。
