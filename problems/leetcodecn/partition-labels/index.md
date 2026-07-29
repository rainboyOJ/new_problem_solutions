---
oj: "leetcodecn"
problem_id: "partition-labels"
title: "划分字母区间"
description: "预处理每个字母最后出现位置，扫描时扩展当前段边界至段内所有字母最远末次位置，到达时切分。"
difficulty: "普及+/提高"
date: 2026-07-29 12:28
toc: true
tags: ["贪心", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/partition-labels/
---

[[TOC]]

### 题意
将字符串划分为尽可能多的片段，同一字母只出现在一个片段中。

### 思路
先预处理每个字母的最后出现位置 `last[c]`。扫描时维护当前段边界 `end`：遇到字符 `c` 时更新 `end = max(end, last[c])`。当扫描位置 `i` 到达 `end` 时，说明当前段内所有字母的末次出现都已包含，可以切分。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$（字母表大小固定）。

### 总结
划分字母区间是贪心的典型：每段尽可能短，但必须包含段内所有字母的末次出现。`end` 的扩展保证了"不遗漏"，到达 `end` 时切分保证了"不冗余"。
