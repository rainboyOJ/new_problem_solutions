---
oj: "leetcodecn"
problem_id: "first-missing-positive"
title: "缺失的第一个正数"
description: "把值 x 放到下标 x-1，最后第一个 a[i] != i+1 即答案，O(n) 时间 O(1) 空间。"
difficulty: "提高+/省选-"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "哈希表", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/first-missing-positive/
---

[[TOC]]

### 题意

未排序整数数组，找出其中没有出现的最小的正整数。要求 O(n) 时间、O(1) 额外空间。

### 思路

排序 O(n log n) 不够快。核心观察：答案一定在 `[1, n+1]` 范围内。把值 `x` 放到下标 `x-1` 的位置（类似原地哈希），然后扫描第一个下标和值不匹配的位置。

- 只关注 `[1, n]` 的值，超出范围的不管。
- 用 swap 循环放置，每个值至多被交换一次。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)，每个元素至多被交换一次。
- 空间复杂度：O(1)，原地交换。

### 总结

"值域与下标映射"是 O(1) 空间哈希的常用手法。利用出题范围 `[1, n]` 把数组本身当作哈希表。
