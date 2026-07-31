---
oj: "shumeng"
problem_id: "CSP201604A"
title: "折点计数"
description: "扫描相邻差值，前后变化方向相反的中间位置就是折点。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201604A
---

[[TOC]]

### 题意

统计销售量数列中由增长转为减少或由减少转为增长的位置。

### 思路

对每个中间位置，比较前后两个差值。相邻销售量保证不同，因此两差值乘积小于 0 当且仅当前后方向不同，当前位置就是折点。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

端点没有前后两天，不能成为折点。利用差值符号可以统一判断峰值和谷值。
