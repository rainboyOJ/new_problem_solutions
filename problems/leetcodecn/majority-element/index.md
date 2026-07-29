---
oj: "leetcodecn"
problem_id: "majority-element"
title: "多数元素"
description: "Boyer-Moore 投票：计数器抵消非多数元素，最终留下的候选即为多数。"
difficulty: "普及-"
date: 2026-07-29 13:01
toc: true
tags: ["技巧", "投票算法"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/majority-element/
---

[[TOC]]

### 题意
找出出现次数超过 n/2 的元素（保证存在）。

### 思路
Boyer-Moore 投票：维护候选 `cand` 和计数 `cnt`。遇到相同则 `cnt++`，不同则 `cnt--`，`cnt` 为 0 时换候选。多数元素数量超过一半，抵消后必然留下。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
Boyer-Moore 投票的核心：多数元素数量超过一半，即使所有非多数元素都来抵消，多数元素仍会留下。正确性依赖多数元素存在的前提。
