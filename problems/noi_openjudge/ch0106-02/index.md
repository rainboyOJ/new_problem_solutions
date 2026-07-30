---
oj: "noi_openjudge"
problem_id: "ch0106-02"
title: "陶陶摘苹果"
description: "把板凳高度加入可达高度后，统计不超过该高度的苹果。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/02/
---

[[TOC]]

### 题意

陶陶站上 $30$ 厘米板凳后，统计十个苹果中她能够碰到的数量。

### 思路

实际可达高度为手能达到的高度加 $30$。枚举苹果高度并统计 `height <= reachable_height` 的个数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定处理十个苹果，时间和额外空间复杂度均为 $O(1)$。

### 总结

题目中的辅助工具先折算进统一阈值，后续只剩简单比较。
