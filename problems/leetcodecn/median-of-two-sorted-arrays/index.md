---
oj: "leetcodecn"
problem_id: "median-of-two-sorted-arrays"
title: "寻找两个正序数组的中位数"
description: "在较短数组上二分分割线，满足左半最大 ≤ 右半最小，由四个边界值计算中位数。"
difficulty: "提高+/省选-"
date: 2026-07-29 11:58
toc: true
tags: ["二分查找", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/median-of-two-sorted-arrays/
---

[[TOC]]

### 题意

给定两个正序数组，找中位数。要求 $O(\log(m+n))$。

### 思路

中位数等价于把合并后数组分成左右两半，使得左半最大 $\leqslant$ 右半最小，且左半元素数 $=$ 右半元素数（或恰好多一个）。

在较短数组 `a` 上二分分割线位置 `i`（`a` 左半取 `a[0..i-1]`），`b` 的分割位置 `j = (m+n+1)/2 - i` 自动确定。四个边界值 `al, ar, bl, br` 分别表示分割线两侧的值（越界用 $\pm\infty$）。

条件 `al <= br && bl <= ar` 满足时分割合法，中位数由 `max(al,bl)` 和 `min(ar,br)` 计算。`al > br` 时 `i` 太大，`bl > ar` 时 `i` 太小。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log(\min(m,n)))$，只在较短数组上二分。
- 空间复杂度：$O(1)$。

### 总结

双数组中位数的核心是"分割线"模型：在较短数组上二分，自动确定另一个数组的分割位置，四个边界值判断合法性并计算结果。`j = (m+n+1)/2 - i` 保证了左半元素数正确。
