---
oj: "noi_openjudge"
problem_id: "ch0111-01"
title: "查找最接近的元素"
description: "用 bisect_left 找到查询值右侧候选，再比较相邻两数的距离。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/01/
---

[[TOC]]

### 题意

在非降序列中回答多次查询：输出与查询值距离最小的元素；距离相同则选较小值。

### 思路

`bisect_left(numbers, target)` 找到第一个不小于查询值的位置。最接近的元素只可能是这个位置或其左邻居；处理越界后比较两边距离。相等时选择左边，正好满足取较小值的规则。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每次查询时间复杂度为 $O(\log n)$，额外空间复杂度为 $O(1)$。

### 总结

有序序列中的“最接近”问题，只需检查二分定位点附近的两个候选。
