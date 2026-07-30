---
oj: "noi_openjudge"
problem_id: "ch0111-03"
title: "矩形分割"
description: "二分竖线位置使左侧面积首次不少于总面积一半，再取同面积的最右位置。"
difficulty: "普及+/提高"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "几何", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/03/
---

[[TOC]]

### 题意

选择整数竖线 $x=k$ 分割若干互不重叠的小矩形，使左侧面积不少于右侧、面积差最小；同样最优时取左侧区域最大的竖线位置。

### 思路

对一个给定的 $x$，每个矩形对左侧的贡献是 `max(0, min(宽, x - 左边界)) * 高`，相加得到单调不减的左侧面积。先二分左侧面积首次达到总面积一半的位置，这给出最小可行面积；若这一面积在一段横坐标上不变，再二分到这段平台最右端，满足题目的第二个要求。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每次面积计算为 $O(n)$，两次二分共 $O(n \log R)$，空间复杂度为 $O(n)$。

### 总结

面积随竖线右移单调不减，因此“最小达到目标”和“平台最右端”都可二分。
