---
oj: "atcoder"
problem_id: "abc085_b"
title: "ABC085B - Kagami Mochi"
description: "统计不同直径的个数即最大层数。"
difficulty: "入门"
date: 2026-07-10 16:21
toc: true
tags: ["贪心", "排序", "c++", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc085_b
---

[[TOC]]

### 题意

下层饼必须比上层饼直径大，每个饼只能用一次。求最多能叠多少层。

### 思路

每个直径只能出现一次，所以统计不同直径的个数就是答案。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(N \log N)$，空间复杂度 $O(N)$。

### 总结

去重计数即可。
