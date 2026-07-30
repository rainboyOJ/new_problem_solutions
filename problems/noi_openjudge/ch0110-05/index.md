---
oj: "noi_openjudge"
problem_id: "ch0110-05"
title: "分数线划定"
description: "按分数降序和报名号升序排序，以计划人数的 150% 位置确定分数线。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/05/
---

[[TOC]]

### 题意

根据计划录取人数的 $150\%$ 确定面试分数线，并输出所有分数不低于分数线的选手。成绩相同的选手按报名号升序输出。

### 思路

先按 `(-分数, 报名号)` 排序。分数线是第 `int(m * 1.5)` 名的成绩，对应 Python 下标 `int(m * 1.5) - 1`。再从排好序的序列中筛出所有分数不低于这条线的选手，自然保持题目要求的输出顺序。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

分数线只决定最低分数，和分数线相同的所有选手都必须保留。
