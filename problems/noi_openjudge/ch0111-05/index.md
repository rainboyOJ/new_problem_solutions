---
oj: "noi_openjudge"
problem_id: "ch0111-05"
title: "派"
description: "二分每块派的面积，用各圆面积的整除结果统计可切份数。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "几何", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/05/
---

[[TOC]]

### 题意

把若干圆形派分给所有朋友和自己，每人得到一块面积相同的派，求这块派的最大面积。

### 思路

半径为 $r$ 的派面积为 $\pi r^2$。假设每块面积为 $x$，一张派能切出 `int(面积 / x)` 块；所有派合计至少有 `F + 1` 块时，$x$ 可行。面积越小可切块数越多，因此可以在 $[0, 最大派面积]$ 上二分。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

二分固定 100 次，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

实数二分不必等到端点相等，迭代足够多次即可保证输出精度。
