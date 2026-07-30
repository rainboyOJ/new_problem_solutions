---
oj: "noi_openjudge"
problem_id: "ch0104-16"
title: "三角形判断"
description: "排序后三边中两条较短边之和大于最长边即可构成三角形。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["几何", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/16/
---

[[TOC]]

### 题意

判断三条正整数线段能否组成三角形。

### 思路

排序后设三边为 $a\leqslant b\leqslant c$。只需检查 $a+b>c$；其余两条三角不等式因边长为正自动成立。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

排序对象数固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

先排序能把三条不等式压缩成“短边和大于最长边”这一条。
