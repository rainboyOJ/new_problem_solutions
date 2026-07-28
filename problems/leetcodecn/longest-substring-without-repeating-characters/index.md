---
oj: "leetcodecn"
problem_id: "longest-substring-without-repeating-characters"
title: "无重复字符的最长子串"
description: "滑动窗口记录字符上次出现位置，左指针直接跳到重复字符后，O(n)。"
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
source: https://leetcode.cn/problems/longest-substring-without-repeating-characters/
---

[[TOC]]

### 题意

给定字符串 s，找出不含重复字符的最长子串的长度。

### 思路

枚举所有子串 O(n²) 会超时。滑动窗口优化：右指针扩展，当遇到重复字符时，左指针直接跳到该字符上次出现位置 + 1，保证窗口始终无重复。

用一个数组 `last[128]` 记录每个字符上次出现的位置（1-indexed）。右指针移动时，左指针取 `max(左指针, last[当前字符])`，然后更新 `last`。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，每个字符被左右指针各访问一次。
- 空间复杂度：O(|Σ|)，字符集大小（ASCII 128）。

### 总结

"记录每个元素上次位置，遇到重复时跳跃左指针"是滑动窗口的一种变体，相比每次移动左指针一格的写法更高效。关键在于左指针只向前移动，不回退。
