---
oj: "noi_openjudge"
problem_id: "ch0106-06"
title: "校门外的树"
description: "用布尔数组标记所有被区间覆盖的位置，再统计未移走的树。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "模拟", "区间", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/06/
---

[[TOC]]

### 题意

数轴 $0$ 到 $L$ 的每个整数位置都有树。多个闭区间内的树被移走，求剩余树数。

### 思路

布尔数组 `removed[position]` 表示该位置的树是否被移走。对每个闭区间 `left` 到 `right` 标记为真，重叠区间重复标记不会影响结果，最后统计为假的位置。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有区间长度总和为 $S$，时间复杂度为 $O(L+S)$，空间复杂度为 $O(L)$。

### 总结

范围不大且只需覆盖与否时，直接标记比处理区间重叠关系更直观。
