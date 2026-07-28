---
oj: "leetcodecn"
problem_id: "sliding-window-maximum"
title: "滑动窗口最大值"
description: "单调递减队列保存候选下标，过期从队首删，较小候选从队尾删，O(n)。"
difficulty: "困难"
date: 2026-07-28 22:05
toc: true
tags: ["队列", "单调队列", "滑动窗口", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/sliding-window-maximum/
---

[[TOC]]

### 题意

给定数组和滑动窗口大小 k，返回每个窗口的最大值。

### 思路

暴力 O(nk) 每个窗口扫一遍最大值。优化：用单调递减队列保存窗口内可能成为最大值的元素下标。

- 队首始终是当前窗口的最大值。
- 新元素入队时，从队尾弹出所有比它小的元素（它们再也不可能成为最大值）。
- 队首超出窗口范围时弹出。

每个元素至多入队出队一次，均摊 O(n)。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，每个元素入队出队各一次。
- 空间复杂度：O(k)，队列最多存 k 个元素。

### 总结

单调队列适用于"滑动窗口最值"问题，"被更大值淘汰"的永久性是保证 O(n) 的关键。该模型与单调栈对称：栈处理的是固定端点向一侧扩展，队列处理的是连续滑动窗口。
