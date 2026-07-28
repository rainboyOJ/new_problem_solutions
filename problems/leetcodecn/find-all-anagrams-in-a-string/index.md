---
oj: "leetcodecn"
problem_id: "find-all-anagrams-in-a-string"
title: "找到字符串中所有字母异位词"
description: "固定长度滑动窗口维护 26 维字母计数，窗口进出各一次，O(n)。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["哈希表", "字符串", "滑动窗口", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/find-all-anagrams-in-a-string/
---

[[TOC]]

### 题意

给定字符串 s 和 p，找出 s 中所有 p 的字母异位词子串的起始下标。

### 思路

暴力排序每个窗口 O(nk log k)。优化：用 26 维计数器维护窗口内字符频次，每次窗口滑动时只更新进出两个字符，然后比较整个计数数组是否归零。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，每个字符进出各一次，每次检查 26 个计数（常数）。
- 空间复杂度：O(1)，固定 26 长度的计数数组。

### 总结

固定长度滑动窗口配合计数数组做"异位词匹配"，是字符串模式匹配的经典模型。窗口滑动时只维护变化的两端，将每次匹配的时间从 O(k log k) 降到 O(1)。
