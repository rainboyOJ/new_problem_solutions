---
oj: "leetcodecn"
problem_id: "search-in-rotated-sorted-array"
title: "搜索旋转排序数组"
description: "每轮二分判断哪一半有序，再判断 target 是否落在该半区，缩小搜索范围。"
difficulty: "普及+/提高"
date: 2026-07-29 11:52
toc: true
tags: ["二分查找", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/search-in-rotated-sorted-array/
---

[[TOC]]

### 题意

给定旋转一次的升序无重复数组，查找 `target` 的下标，不存在返回 `-1`。要求 $O(\log n)$。

### 思路

虽然数组整体无序，但二分后必有一半是有序的。判断方法：若 `nums[l] <= nums[mid]`，左半有序；否则右半有序。

确定有序半区后，判断 `target` 是否落在该半区的值域内：

- 左半有序且 `nums[l] <= target < nums[mid]`：`r = mid - 1`，搜索左半。
- 左半有序但 `target` 不在左半：`l = mid + 1`，搜索右半。
- 右半有序且 `nums[mid] < target <= nums[r]`：`l = mid + 1`，搜索右半。
- 右半有序但 `target` 不在右半：`r = mid - 1`，搜索左半。

每轮排除一半，保证 $O(\log n)$。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log n)$。
- 空间复杂度：$O(1)$。

### 总结

旋转数组二分的核心观察：二分后必有一半有序。先判断哪半有序，再判断 target 是否在该半区，从而缩小范围。`nums[l] <= nums[mid]` 的等号处理了 `l == mid` 的情况。
