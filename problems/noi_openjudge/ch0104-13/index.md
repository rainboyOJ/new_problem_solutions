---
oj: "noi_openjudge"
problem_id: "ch0104-13"
title: "分段函数"
description: "按 x 的三个区间依次选择对应函数并保留三位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "条件判断", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/13/
---

[[TOC]]

### 题意

按 $[0,5)$、$[5,10)$、$[10,20)$ 三个区间计算不同的函数值。

### 思路

输入已保证范围，因此先判断 `x < 5`，再判断 `x < 10`，最后的 `else` 就是第三段。这样边界 5 和 10 自动落入后一段。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

有序区间的分段函数按上界依次判断，能减少重复范围条件。
