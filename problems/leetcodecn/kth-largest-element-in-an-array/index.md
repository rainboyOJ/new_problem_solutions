---
oj: "leetcodecn"
problem_id: "kth-largest-element-in-an-array"
title: "数组中的第K个最大元素"
description: "维护大小为 k 的最小堆，堆顶即为第 k 大元素。"
difficulty: "普及+/提高"
date: 2026-07-29 12:15
toc: true
tags: ["堆", "优先队列", "排序"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/kth-largest-element-in-an-array/
---

[[TOC]]

### 题意

找出数组中第 `k` 大的元素（排序后倒数第 `k` 个）。

### 思路

维护一个大小为 `k` 的最小堆。每次插入元素后，若堆大小超过 `k`，弹出堆顶最小值。最终堆中保留最大的 `k` 个元素，堆顶就是第 `k` 大。

最小堆而非最大堆的关键理解：我们要保留最大的 `k` 个元素，所以每次弹出的是堆中最小的那个——即这 `k` 个中"最不够格"的。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \log k)$，每个元素堆操作 $O(\log k)$。
- 空间复杂度：$O(k)$，堆最多存 `k` 个元素。

### 总结

第 `k` 大/小元素用大小为 `k` 的堆：第 `k` 大用最小堆（弹小留大），第 `k` 小用最大堆（弹大留小）。堆顶即答案。
