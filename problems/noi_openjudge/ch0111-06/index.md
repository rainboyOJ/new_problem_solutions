---
oj: "noi_openjudge"
problem_id: "ch0111-06"
title: "月度开销"
description: "二分最大月度开销，用一次贪心扫描统计所需财政周期数。"
difficulty: "普及+/提高"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/06/
---

[[TOC]]

### 题意

将连续的每天开销划分为至多 $M$ 个连续财政周期，最小化其中最大周期的开销。

### 思路

二分最大允许开销 `limit`。从前向后尽量把当天放进当前周期，若会超过 `limit` 就新开一个周期；这种贪心在给定上限下使用的周期数最少。若周期数不超过 $M$，说明该上限可行。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log S)$，其中 $S$ 是所有开销之和；空间复杂度为 $O(n)$。

### 总结

“最小化最大值”常转化为“给定上限是否可行”的二分判定。
