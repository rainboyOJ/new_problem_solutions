---
oj: "leetcodecn"
problem_id: "merge-intervals"
title: "合并区间"
description: "按左端点排序，遍历时维护当前合并区间，相交则扩右端，否则输出并重开。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "排序", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/merge-intervals/
---

[[TOC]]

### 题意

给定区间集合，合并所有重叠区间。

### 思路

暴力反复合并 O(n²) 效率低。排序后只需一次扫描：按左端点排序，维护当前合并区间。新区间与当前区间相交则扩展右端点，否则输出当前区间并开启新区间。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n log n)，排序占主导。
- 空间复杂度：O(log n) 或 O(n)，取决于排序实现。

### 总结

区间合并类的核心预处理是排序。排序后只需要看相邻区间是否相交，不需要反复回溯。该模型也适用于区间交、区间差等变体。
