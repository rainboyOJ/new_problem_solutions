---
oj: "noi_openjudge"
problem_id: "ch0105-19"
title: "救援"
description: "累计每个屋顶的往返航行时间和上下船时间，最后向上取整。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["几何", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/19/
---

[[TOC]]

### 题意

救生船从原点往返各屋顶。航速为 50 米/分钟，每人上船 1 分钟、下船 0.5 分钟，求总分钟数向上取整。

### 思路

坐标 $(x,y)$ 到原点距离用 `math.hypot(x, y)`。往返航行耗时为 `2 * distance / 50`，每人上下船共 1.5 分钟。累计所有屋顶后用 `math.ceil` 向上取整。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

多地点独立往返时，总时间等于逐地点时间之和；“精确到分钟”要求最后向上取整。
