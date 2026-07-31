---
oj: "shumeng"
problem_id: "CSP201509A"
title: "数列分段"
description: "线性扫描数列，每次相邻数字变化时计入一个新的连续段。"
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
source: https://oj.shumeng.tech/p/CSP201509A
---

[[TOC]]

### 题意

统计数列中极长连续相同子数组的数量。

### 思路

先看逐段跳过相同数字的写法：

@include-code(./brute.cpp, cpp)

第一个数字一定形成第一段。之后扫描每个数字，若它和前一个不同，说明新的一段从这里开始，答案加一。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

### 总结

连续段的边界恰好是相邻数字不相同的位置。保留前一个数字即可在线统计，无需存储整个数列。
