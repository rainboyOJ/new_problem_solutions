---
oj: "usaco"
problem_id: "1112"
title: "Just Green Enough"
description: "用 min=100 转化为全 >=100 子矩形数减全 >=101 子矩形数，再固定上下边界降成一维计数。"
difficulty: "普及+/提高"
date: 2026-07-11 21:27
toc: true
tags: ["矩阵", "枚举", "前缀和", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1112
---

[[TOC]]

### 题意

给定一个 $N\times N$ 矩阵，要求统计有多少个子矩形的最小值恰好等于 `100`。

### 思路

先看暴力：枚举所有子矩形，直接扫描内部求最小值。

@include-code(./brute.cpp, cpp)

正解先做一个转化：

```text
min == 100 的子矩形数量
= 所有元素 >= 100 的子矩形数量
- 所有元素 >= 101 的子矩形数量
```

所以只需要会计算：给定阈值 `limit`，有多少个子矩形满足所有元素都 $>= limit$。

固定子矩形的上边界 `top` 和下边界 `bottom`。对每一列，判断这一列在 `top..bottom` 之间是否全部满足阈值。

例如某个上下边界下得到一维 01 序列：

| 列 | 1 | 2 | 3 | 4 | 5 |
| --- | --- | --- | --- | --- | --- |
| 是否整列合法 | 1 | 1 | 0 | 1 | 1 |

连续的 `1` 段才能作为左右边界。长度为 2 的连续 1 段贡献：

```text
1 + 2 = 3
```

个左右区间。

实现时固定 `top`，逐渐增加 `bottom`。用 `all_good[col]` 维护当前上下边界内第 `col` 列是否仍然全部满足阈值。每增加一行，只要这一行某列小于 `limit`，这一列就变成 0。

扫描 `all_good` 时维护当前连续 1 的长度 `run`：

```text
遇到 1：run++, ans += run
遇到 0：run = 0
```

最后答案就是：

```text
count_at_least(100) - count_at_least(101)
```

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

枚举上下边界和列，`count_at_least` 是 $O(N^3)$。

调用两次，时间复杂度仍为 $O(N^3)$。

空间复杂度为 $O(N^2)$。

### 总结

本题的关键是补集计数：最小值恰好为 `100`，可以拆成两个“全都不小于某个阈值”的计数。

固定上下边界后，二维矩形计数变成一维连续 1 子段计数，这是常见的二维降维技巧。
