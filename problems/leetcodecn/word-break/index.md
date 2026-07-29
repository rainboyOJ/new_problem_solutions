---
oj: "leetcodecn"
problem_id: "word-break"
title: "单词拆分"
description: "dp[i] 表示前 i 个字符是否可拆分，枚举断点 j，若 dp[j] 且 s[j:i] 在字典中则 dp[i]=true。"
difficulty: "普及+/提高"
date: 2026-07-29 12:39
toc: true
tags: ["动态规划", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/word-break/
---

[[TOC]]

### 题意
判断字符串能否拆分为字典中的单词。

### 思路
`dp[i]` 表示前 `i` 个字符是否可拆分。枚举断点 `j`，若 `dp[j]` 且 `s[j:i]` 在字典中，则 `dp[i] = true`。找到即 break，无需继续枚举。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n^2)$，每个 `i` 枚举所有 `j`。
- 空间复杂度：$O(n)$。

### 总结
单词拆分是"前缀可拆分"的典型 DP：`dp[i]` 的含义是"前 i 个字符可拆分"，枚举断点找子串。
