---
oj: "leetcodecn"
problem_id: "find-minimum-in-rotated-sorted-array"
title: "寻找旋转排序数组中的最小值"
description: "比较中点与右端点，保留最小值所在闭区间，最终 l 指向最小元素。"
difficulty: "普及+/提高"
date: 2026-07-29 11:55
toc: true
tags: ["二分查找", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/
---

[[TOC]]

### 题意

给定旋转一次的升序无重复数组，找到最小元素。要求 $O(\log n)$。

### 思路

比较 `nums[mid]` 与 `nums[r]`：若 `nums[mid] < nums[r]`，右半区间 `[mid, r]` 有序，最小值一定在 `[l, mid]`（含 mid）；否则右半区间无序（旋转点在右半），最小值在 `[mid+1, r]`。

循环条件 `l < r`（而非 `l <= r`），因为当 `l == r` 时区间只有一个元素，即为答案。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log n)$。
- 空间复杂度：$O(1)$。

### 总结

旋转数组找最小值与找 target 的二分模式不同：不判断"哪半有序"，而是比较中点与右端点来决定最小值落在哪半。`nums[mid] < nums[r]` 说明 `[mid, r]` 有序，最小值不可能在 mid 右侧（不含 mid），所以 `r = mid`。
