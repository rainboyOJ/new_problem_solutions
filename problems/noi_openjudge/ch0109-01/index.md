---
oj: "noi_openjudge"
problem_id: "ch0109-01"
title: "查找特定的值"
description: "用列表 index 查找目标值的首次位置，不存在时输出 -1。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "查找", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0109/01/
---

[[TOC]]

### 题意

在下标从 $1$ 开始的整数序列中，输出给定值第一次出现的位置。

### 思路

先用 `target in numbers` 判断存在性，再用 `index` 得到零基下标并加一；不存在时输出 `-1`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，序列空间为 $O(n)$。

### 总结

题目下标与 Python 下标不同，输出前要完成一次加一转换。
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)
