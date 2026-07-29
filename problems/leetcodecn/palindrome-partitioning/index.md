---
oj: "leetcodecn"
problem_id: "palindrome-partitioning"
title: "分割回文串"
description: "回溯枚举每段终点，只递归回文前缀，预处理区间回文表加速判断。"
difficulty: "普及+/提高"
date: 2026-07-29 11:35
toc: true
tags: ["回溯", "枚举", "字符串", "动态规划"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/palindrome-partitioning/
---

[[TOC]]

### 题意

给定字符串 `s`，将其分割成若干子串，使每个子串都是回文串。返回所有可能的分割方案。

### 思路

最直接的思路是枚举所有切分方式，逐一检查每段是否回文：

@include-code(./brute.cpp, cpp)

brute.cpp 每次枚举 `s[i..j]` 作为下一段，只有当它是回文时才递归 `dfs(j+1)`。这种"只递归回文前缀"的剪枝已经排除了大量无效分支。

优化的关键是：将回文判断从 $O(k)$ 降到 $O(1)$。预处理 `pal[i][j]` 表示 `s[i..j]` 是否回文：`pal[i][j] = (s[i]==s[j]) && (j-i<2 || pal[i+1][j-1])`，从右下向左上填充。递归时只需查表，不再逐字符比较。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：最坏 $O(n \cdot 2^n)$，每个位置切或不切，预处理 $O(n^2)$。
- 空间复杂度：$O(n^2)$，回文表。

### 总结

分割类回溯的核心是"枚举下一段终点，只递归合法前缀"。预处理区间回文表将判断从 $O(k)$ 降到 $O(1)$，是经典的"预处理加速回溯"模式。
