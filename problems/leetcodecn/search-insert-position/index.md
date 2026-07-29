---
oj: "leetcodecn"
problem_id: "search-insert-position"
title: "搜索插入位置"
description: "二分查找 lower_bound，返回第一个 ≥ target 的位置，即插入位置。"
difficulty: "普及-"
date: 2026-07-29 11:45
toc: true
tags: ["二分查找", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/search-insert-position/
---

[[TOC]]

### 题意

给定升序无重复数组 `nums` 和目标值 `target`，返回 `target` 在数组中的索引；若不存在，返回按顺序插入的位置。要求 $O(\log n)$。

### 思路

本题本质是求 `lower_bound`：区间内第一个 $\geqslant \text{target}$ 的位置。C++ 直接调用 `lower_bound`；Python 手写二分，谓词 `nums[m] >= target` 缩右区间，`nums[m] < target` 缩左区间。

关键理解：`lower_bound` 返回的位置既是"已存在元素的索引"（若该元素等于 `target`），也是"应插入的位置"（若不存在）。二者统一在同一次二分中。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log n)$。
- 空间复杂度：$O(1)$。

### 总结

`lower_bound` 是二分查找的基础操作：找第一个满足谓词的位置。本题谓词是 $\geqslant \text{target}$，返回值同时覆盖"找到"和"插入"两种语义。
