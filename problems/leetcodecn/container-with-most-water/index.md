---
oj: "leetcodecn"
problem_id: "container-with-most-water"
title: "盛最多水的容器"
description: "双指针维护区间，面积由短板决定，每次移动较矮一侧，O(n)。"
difficulty: "中等"
date: 2026-07-28 22:03
toc: true
tags: ["双指针", "贪心", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/container-with-most-water/
---

[[TOC]]

### 题意

给定 n 条垂线的高度，找出两条线，使它们与 x 轴构成的容器能容纳最多的水。

### 思路

暴力枚举所有 (i,j) 对 O(n²)。优化：左右指针从两端向中间移动，每次移动较矮的一侧。

正确性证明：设当前左右指针为 l、r，面积 = (r-l) × min(h[l], h[r])。如果移动较高的一侧，新面积的高度不会超过 min(h[l], h[r])，而宽度变小，面积一定不会更大。所以只能移动较矮的一侧，才有可能获得更大的面积。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，指针各移动一次。
- 空间复杂度：O(1)。

### 总结

"短板决定、移动短板"是双指针求区间最值问题的经典模型。关键在于证明移动长板不可能得到更优解。
