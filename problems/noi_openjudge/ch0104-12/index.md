---
oj: "noi_openjudge"
problem_id: "ch0104-12"
title: "骑车与走路"
description: "将两种时间同乘 6 后用整数比较骑车、步行和相等情况。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/12/
---

[[TOC]]

### 题意

步行速度为 1.2 米/秒，骑车速度为 3 米/秒且额外耗时 50 秒，比较哪种方式更快。

### 思路

步行时间为 $5d/6$，骑车时间为 $d/3+50$。两边同乘 6 后比较 `5*d` 与 `2*d+300`，全程使用整数，避免浮点数相等比较。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

比较含小数的公式时，可先消去分母，把问题转为精确整数比较。
