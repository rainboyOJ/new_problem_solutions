---
oj: "atcoder"
problem_id: "abc088_b"
title: "ABC088B - Card Game for Two"
description: "降序排序后，Alice 取偶数位 Bob 取奇数位，输出分差。"
difficulty: "入门"
date: 2026-07-10 16:11
toc: true
tags: ["贪心", "排序", "c++", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc088_b
---

[[TOC]]

### 题意

$N$ 张牌，Alice 和 Bob 轮流取最大的牌，Alice 先手。求 Alice 总分 - Bob 总分。

### 思路

降序排序后 Alice 取偶数位、Bob 取奇数位，差即为答案。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(N \log N)$，空间复杂度 $O(N)$。

### 总结

贪心取最大 + 交替分配。
