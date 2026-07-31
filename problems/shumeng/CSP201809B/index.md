---
oj: "shumeng"
problem_id: "CSP201809B"
title: "买菜"
description: "用两个有序区间指针逐段求交，推进结束时刻更早的一方。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["双指针", "区间", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201809B
---

[[TOC]]

### 题意

两人各有 `n` 个按时间顺序排列且互不重叠的装车区间。求所有同时装车时间的总长度，区间 `[l,r]` 的长度为 `r-l`。

### 思路

小数据可以枚举第一人的每一段与第二人的每一段，交集长度为 `max(0,min(r1,r2)-max(l1,l2))`。

@include-code(./brute.cpp, cpp)

因为两组区间内部都有序且互不重叠，只需维护当前的第 `i`、第 `j` 段。先累加这两段的交集；结束时刻更早的区间不可能再和对方后续区间相交，因此推进它的指针。若结束时刻相等，推进任意一个指针都正确，代码推进第二个指针。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

两个指针各至多前进 `n` 次，时间复杂度为 $O(n)$，额外空间复杂度为 $O(n)$。

### 总结

处理两组有序、不重叠区间时，不必枚举所有区间对。当前两段比较后，结束更早的一段已没有后续机会，这正是双指针能线性推进的原因。
