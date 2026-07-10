---
oj: "atcoder"
problem_id: "abc083_b"
title: "ABC083B - Some Sums"
description: "遍历 1..N，递归拆位计算各位数字之和，筛选在 [A,B] 内的数并求和。"
difficulty: "入门"
date: 2026-07-10 11:27
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc083_b
---

[[TOC]]

### 题意

求 $1$ 到 $N$ 中，各位数字之和在 $[A,B]$ 内的所有数的总和。

### 思路

遍历 $1..N$，递归拆位计算各位和，筛选符合条件的数累加。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(N \log_{10} N)$，空间复杂度 $O(1)$。

### 总结

递归拆位 + 列表推导式 + `sum` 求和。
