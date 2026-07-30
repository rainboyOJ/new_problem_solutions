---
oj: "noi_openjudge"
problem_id: "ch0105-03"
title: "均值"
description: "读取一行浮点样本并用 sum/count 计算四位小数均值。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/03/
---

[[TOC]]

### 题意

给出一行 $n$ 个浮点样本，输出均值，保留四位小数。

### 思路

`input().split()` 按空白切分样本，`map(float, ...)` 按需转换。`sum(samples) / count` 是均值，`.4f` 负责定点输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

不需要重复访问数据时，`map` 可直接交给 `sum`，避免额外列表。
