---
oj: "usaco"
problem_id: "1275"
title: "Leaders"
description: "利用名单只能向右延伸的性质，把合法 leader pair 归到最早 G 或最早 H 两类中计数。"
difficulty: "普及-"
date: 2026-07-11 16:55
toc: true
tags: ["枚举", "思维", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1275
---

[[TOC]]

### 题意

有 `N` 头牛排成一行，每头牛是 `G` 或 `H`。

第 `i` 头牛写下的名单是连续区间 `[i, E_i]`。

每个品种恰好有一个 leader。一个 leader 必须满足下面两个条件之一：

1. 它的名单包含本品种所有牛；
2. 它的名单包含另一个品种的 leader。

求有多少对 `(G leader, H leader)` 可能成立。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

这个暴力直接枚举 `G leader` 和 `H leader`，再按题意检查两头牛是否都满足 leader 条件。它很适合理解题意，但枚举 pair 再检查覆盖关系，最坏会到 $O(N^3)$。

满分做法的关键是：名单只能向右延伸。

如果两个 leader 都没有覆盖本品种所有牛，那么它们就必须互相出现在对方名单中。可是两个不同位置不可能互相在对方右侧，所以这是不可能的。

因此任意合法 pair 中，至少有一个 leader 必须覆盖本品种所有牛。

能覆盖本品种所有牛的 leader 又只能是本品种最靠前的牛。因为如果它前面还有同品种牛，它的名单从自己开始，无法包含前面的同品种牛。

所以我们只需要找到四个位置：

- `first_g`、`last_g`：最早和最晚的 `G`；
- `first_h`、`last_h`：最早和最晚的 `H`。

若 `E[first_g] >= last_g`，则 `first_g` 可以作为 `G leader`。此时另一个 `H leader` 如果不是 `first_h`，它就不能覆盖所有 `H`，只能靠名单包含 `first_g`，也就是满足：

```text
i <= first_g <= E[i]
```

对 `H` 做同样的对称处理。

最后要单独判断 `(first_g, first_h)` 这一对。因为它可能同时落入“最早 `G` 做 leader”和“最早 `H` 做 leader”两类，如果不单独处理就容易重复计数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

只需要扫描常数次数组。

时间复杂度为 $O(N)$，空间复杂度为 $O(N)$。

### 总结

本题的突破点不是枚举技巧，而是方向性。

名单只能向右延伸，排除了两个 leader 互相包含的可能，于是合法 pair 一定围绕最早的 `G` 或最早的 `H` 展开。把这两个最早位置单独拿出来分类计数，就能线性完成。
