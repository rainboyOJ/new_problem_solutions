---
oj: "luogu"
problem_id: "P2822"
difficulty: "普及/提高-"
title: "[NOIP 2016 提高组] 组合数问题"
description: "用 Pascal 递推预处理组合数对 k 的余数，再用二维前缀和回答可整除数量。"
date: 2026-06-22 23:14
toc: true
tags: ["组合计数", "动态规划", "前缀和"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2822
---

[[TOC]]

### 题意

给定固定的 `k` 和多组询问 `(n,m)`。对每组询问，统计有多少对 `(i,j)` 满足：

```text
0 <= i <= n
0 <= j <= min(i,m)
k | C(i,j)
```

### 思路

朴素做法是每个询问重新枚举所有 `(i,j)` 并判断组合数是否能被 `k` 整除。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

询问很多，必须预处理。因为只关心 `C(i,j) mod k`，可以直接用 Pascal 递推：

```text
C(i,j) = C(i-1,j-1) + C(i-1,j)
```

在每一步对 `k` 取模。如果 `C(i,j) mod k == 0`，就把位置 `(i,j)` 标记为 `1`。

接着对这张 `bad` 表做二维前缀和。由于 `j>i` 的位置本来就不是合法组合数，我们让它们保持 `0`。这样询问 `(n,m)` 的答案就是矩形 `0..n, 0..min(n,m)` 中 `bad` 的总和。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理时间 $O(2000^2)$，每次询问 $O(1)$。

空间复杂度 $O(2000^2)$。

### 总结

本题的重点是把大量询问转成预处理。组合数递推负责判断整除，二维前缀和负责快速统计。
