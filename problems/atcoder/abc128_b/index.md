---
oj: "atcoder"
problem_id: "abc128_b"
title: "B - Guidebook"
description: "按城市名升序、分数降序排序后输出原始编号。"
difficulty: "入门"
date: 2026-07-10 21:42
toc: true
tags: ["排序", "c++", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abc128/tasks/abc128_b
---

[[TOC]]

### 题意

按城市字典序升序、同城市按分数降序排列，输出餐厅编号。

### 思路

自定义排序：先城市名，再分数（降序）。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(N \log N)$，空间复杂度 $O(N)$。

### 总结

多关键字排序：`sortOn (city, Down score)`。
