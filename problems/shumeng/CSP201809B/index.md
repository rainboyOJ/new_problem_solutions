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

## 形式化题目

给定两组互不重叠且按时间递增排列的闭区间 $\{[a_i, b_i]\}_{i=1}^n$ 与 $\{[c_i, d_i]\}_{i=1}^n$，区间 $[s, t]$ 的长度为 $t - s$。求两组区间交叠部分的总长度，即

$$
\sum_{1\le i,j\le n} \max(0,\ \min(b_i, d_j) - \max(a_i, c_j)).
$$

## 思路

### 朴素做法

小数据可以枚举第一人的每一段与第二人的每一段，两段相交时累加交集长度 $\max(0,\min(r_1,r_2)-\max(l_1,l_2))$。这一做法时间复杂度 $O(n^2)$，作为对拍基准。

@include-code(./brute.cpp, cpp)

### 双指针线性推进

因为两组区间内部都有序且互不重叠，只需维护当前的小 H 段 $i$ 与小 W 段 $j$。

1. 先累加这两段的交集长度。
2. 结束时刻更早的区间不可能再和对方后续任何区间相交，因此推进它的指针。

当结束时刻相等时，推进任意一方都正确，代码约定推进第二个指针。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：两个指针各至多前进 $n$ 次，$O(n)$。
- 空间：保存两组区间，$O(n)$。

## 总结

处理两组有序、不重叠的区间时，不必枚举所有区间对。当前两段比较后，结束更早的一段已没有后续机会，这正是双指针能线性推进的原因。