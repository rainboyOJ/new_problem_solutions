---
oj: "leetcodecn"
problem_id: "longest-consecutive-sequence"
title: "最长连续序列"
description: "放入集合，只从 x-1 不存在的起点向后扩展，每个数至多被访问一次，均摊 O(n)。"
difficulty: "中等"
date: 2026-07-28 22:01
toc: true
tags: ["哈希表", "集合", "数组", "cpp"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/longest-consecutive-sequence/
---

[[TOC]]

### 题意

给定未排序整数数组，找出数字连续的最长序列的长度。要求 O(n) 时间。

例如 `[100,4,200,1,3,2]`，最长连续序列为 `[1,2,3,4]`，长度 4。

### 思路

先将所有数放入哈希集合，这样 O(1) 查值。

若对每个数都向后递增查找，总复杂度会退化到 O(n²)。关键优化是：**只从序列起点开始扩展**。当前数 `x` 如果存在前驱 `x-1` 在集合中，说明它不是起点，跳过不扩展；只有 `x-1` 不存在时才从 `x` 开始向后数长度。这样每个数最多被访问一次。

@include-code(./brute.cpp, cpp)

排序后一次扫描是最易懂的基线，但不符合进阶 O(n) 要求。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

核心正确性论证：设最长连续序列为 `[s, s+1, ..., s+L-1]`，则 `s-1` 一定不在集合中（否则可以更长），因此枚举到 `s` 时会被当作起点扩展，得到长度 L。其他数要么是序列中间（被跳过），要么扩展出的长度更短，不影响全局最大值。

### 复杂度

- 时间复杂度：O(n)，每个数至多被起点检查和扩展各一次。集合查询和插入均摊 O(1)。
- 空间复杂度：O(n)，存储集合。

### 总结

"只从不存在前驱的起点扩展"是一种经典的哈希集合减肥技巧——不是每个元素都需要执行完整扫描，只有可能成为答案起点的元素才值得展开。这种"利用起点性质跳过无效枚举"的思路在有向图找最长链等问题中也会出现。
