---
oj: "usaco"
problem_id: "1203"
title: "Sleeping in Class"
description: "枚举最终保留段数，把数组切成若干个和相等的连续段，最大段数对应最少合并次数。"
difficulty: "普及-"
date: 2026-07-11 17:36
toc: true
tags: ["枚举", "前缀和", "贪心", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1203
---

[[TOC]]

### 题意

给定数组 `a`。一次操作可以合并两个相邻元素，合并后的值是它们的和。

求最少多少次操作，可以让最终数组中的所有元素相等。

### 思路

先看一个小数据 BFS 暴力：

@include-code(./brute.cpp, cpp)

这个暴力把当前数组看成状态，每一步枚举合并哪一对相邻元素。BFS 第一次到达“所有元素相等”的状态时，步数就是最少操作次数。

满分做法不枚举操作顺序，而是看最终留下多少段。

如果最终留下 `r` 个元素，那么合并次数就是：

```text
N - r
```

要让操作次数最少，就要让 `r` 尽量大。

合并不会改变总和。如果最终 `r` 个元素全相等，那么每个元素都必须是：

```text
total_sum / r
```

所以 `r` 必须整除 `total_sum`。

对于一个固定的 $target_sum = total_sum / r$，从左到右累加：

- 当前段和小于 `target_sum`，继续加；
- 当前段和等于 `target_sum`，切出一段；
- 当前段和大于 `target_sum`，这个 `r` 不可行。

从 $r = N$ 开始往下枚举，第一个可行的 `r` 最大，答案就是 `N-r`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设 `d` 是 `total_sum` 的因子数量。

时间复杂度为 $O(N \cdot d)$，空间复杂度为 $O(N)$。

### 总结

本题的关键转换是：最少合并次数等价于最大化最终段数。

最终每个数都是原数组的一段连续和，因此枚举段数并检查能否切成等和连续段即可。
