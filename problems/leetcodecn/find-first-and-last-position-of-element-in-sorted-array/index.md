---
oj: "leetcodecn"
problem_id: "find-first-and-last-position-of-element-in-sorted-array"
title: "在排序数组中查找元素的第一个和最后一个位置"
description: "两次二分分别找 target 的 lower_bound 与 upper_bound-1，组合得到起止位置。"
difficulty: "普及+/提高"
date: 2026-07-29 11:05
toc: true
tags: ["二分查找", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
---

[[TOC]]

### 题意

给定非递减排序的整数数组 `nums` 和整数 `target`，返回 `target` 在数组中的起止下标 `[first, last]`；不存在则返回 `[-1, -1]`。

要求时间复杂度 $O(\log n)$。

### 思路

线性扫描可以找到答案，但需要 $O(n)$ 时间。利用数组有序性，可以用两次二分将复杂度降到 $O(\log n)$：

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素解线性扫描整个数组，时间 $O(n)$，不满足进阶要求。

优化的关键是：`lower_bound` 返回第一个 $\geqslant \text{target}$ 的位置，`upper_bound` 返回第一个 $> \text{target}$ 的位置。若 `lower_bound` 所指元素恰好等于 `target`，则 `lower_bound` 就是起始下标，`upper_bound - 1` 就是终止下标；若不等于，说明 `target` 不存在，返回 `[-1, -1]`。

判断条件 `l > r`（即 `lower_bound > upper_bound - 1`）统一覆盖了空数组、`target` 不存在和 `target` 越界三种情况。

Python 实现用同一个 `bs` 函数，参数 `left=True` 时行为同 `lower_bound`（$\geqslant$），`left=False` 时行为同 `upper_bound`（$>$）。谓词 `nums[m] > target or (left and nums[m] == target)` 在左界模式下把等于也视为"往左缩"，右界模式下只有严格大于才缩左。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log n)$，两次二分各扫描一次，每次比较 $O(1)$。
- 空间复杂度：$O(1)$，只用到常数个变量。

### 总结

在有序数组上查找边界，核心是把"找第一个/最后一个等于"转化为标准二分谓词：左界用 $\geqslant$（`lower_bound`），右界用 $>$（`upper_bound`），两者之差即为出现区间长度。`l > r` 是判断不存在最简洁的条件。
