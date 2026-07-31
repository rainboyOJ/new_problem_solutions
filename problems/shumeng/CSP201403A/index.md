---
oj: "shumeng"
problem_id: "CSP201403A"
title: "相反数"
description: "用偏移量数组记录已出现整数，读到 x 时查询相反数 -x 是否存在。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["数组", "计数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201403A
---

[[TOC]]

### 题意

给定若干互不相同的非零整数，统计其中有多少个无序相反数对。

### 思路

朴素做法直接枚举所有下标对：

@include-code(./brute.cpp, cpp)

由于数值范围只有 $[-1000,1000]$，用 `seen[v+1000]` 记录整数 `v` 是否已出现即可。读到当前数 `x` 时，先检查此前是否出现过 `-x`；若出现，答案加一；再标记 `x` 已出现。

每对相反数只会在后读到的那个数处理时计数一次。输入互不相同，因此不会重复计数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，`seen` 的长度固定，空间复杂度为 $O(1)$。

### 总结

值域较小时，存在性查询可直接用偏移量数组实现。关键顺序是先查 `-x`，再标记 `x`。
