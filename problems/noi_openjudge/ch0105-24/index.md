---
oj: "noi_openjudge"
problem_id: "ch0105-24"
title: "正常血压"
description: "维护当前连续正常次数和历史最大值，求最长正常时段。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/24/
---

[[TOC]]

### 题意

若收缩压和舒张压都在给定闭区间内则正常，求连续正常血压的最长小时数。

### 思路

维护 `current` 表示以当前时刻结尾的连续正常长度，`longest` 记录历史最大值。正常时递增并更新最大值，异常时将 `current` 清零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

最长连续段的通用状态是“当前段长度”和“历史最大长度”。
