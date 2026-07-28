---
oj: "leetcodecn"
problem_id: "minimum-window-substring"
title: "最小覆盖子串"
description: "滑动窗口维护 need/have 计数，右端扩张满足需求，左端收缩到刚好不满足，O(n)。"
difficulty: "困难"
date: 2026-07-28 22:05
toc: true
tags: ["哈希表", "字符串", "滑动窗口", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/minimum-window-substring/
---

[[TOC]]

### 题意

给定字符串 s 和 t，找出 s 中包含 t 所有字符的最短子串。

### 思路

滑动窗口：右指针不断扩展直到覆盖 t 的所有字符，然后左指针收缩到刚好不满足，记录最短长度。

用 `need[128]` 计数 t 中各字符的需求，`need` 表示仍有需求的字符种类数。窗口滑动时：
- 右指针字符入窗口，若其需求变为 0，`have` 加一。
- 当 `have == need` 时说明当前窗口满足要求，尝试收缩左指针。
- 左指针字符出窗口，若其需求变为 1，`have` 减一，窗口不再满足。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，左右指针各移动一次。
- 空间复杂度：O(|Σ|)，字符集大小。

### 总结

最小覆盖子串是滑动窗口的进阶模型：右端扩张满足约束，左端收缩寻找最优。用 `need/have` 变量代替每次比较整个计数数组，将 O(n·|Σ|) 优化到 O(n)。
