---
oj: "luogu"
problem_id: "P1182"
title: "数列分段 Section II"
description: "二分最大段和，用从左到右尽量装满当前段的贪心检查最少段数。"
difficulty: "普及/提高-"
date: 2026-06-22 20:57
toc: true
tags: ["二分答案", "贪心"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1182
---

[[TOC]]

### 题意

给定一个正整数序列，要把它分成 `M` 段，每段连续。

要求最小化所有段中最大的段和。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力 DP 可以枚举分段点，但数据范围更适合二分答案。

设答案上限为 `limit`。我们只需要判断：能否把序列分成不超过 `M` 段，并且每段和都不超过 `limit`。

检查方法很简单：从左到右扫描，当前段能放就继续放；如果再放会超过 `limit`，就新开一段。

这样得到的是在 `limit` 限制下的最少段数。如果最少段数不超过 `M`，说明 `limit` 可行；否则不可行。

可行性随 `limit` 增大而单调变好，所以可以二分最小可行值。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每次检查为 $O(n)$，二分答案范围，总时间复杂度为：

```text
O(n log sum)
```

空间复杂度为 $O(n)$。

### 总结

本题是典型的“最大值最小”二分答案。

关键是固定答案后用贪心检查最少段数：每段尽量往右扩展，不会让后面更难分，因此这个检查是正确的。
