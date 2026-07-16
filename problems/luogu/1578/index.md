---
oj: "luogu"
problem_id: "P1578"
title: "[WC2002] 奶牛浴场"
description: "枚举经过产奶点的左边界并收紧上下界，同时单独扫描贴场地左边界的最大空白纵缝。"
difficulty: "提高+/省选-"
date: 2026-07-16 18:25
toc: true
tags: ["计算几何", "枚举", "扫描线", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1578
---

[[TOC]]

### 题意

在矩形场地内放置不含任何产奶点内部的最大轴对齐矩形；点允许位于浴场边界。

### 思路

最大矩形的左边要么贴场地左边界，要么经过某个产奶点。

贴左边界时，按 x 扫描点并动态维护已进入内部的 y 坐标最大间隙。左边经过点 `(left,anchor_y)` 时，向右扫描并用遇到的点收紧 `lower/upper`；同高内部点会把可选纵向区间分成锚点上方或下方两部分。每个新 x 在加入该竖线上的点之前结算面积，因为点可以位于右边界。

### Python 知识

- `bisect` 维护有序 y 坐标，`Counter + heapq` 维护当前最大纵缝。
- `set` 去掉重复产奶点，它们不会增加约束。
- 算法为 $O(n^2)$，但内层只做整数比较，适合 $n\le5000$。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

### 总结

最大空矩形必有边界贴场地或穿过障碍点，枚举这条支撑边即可收紧另一维。
