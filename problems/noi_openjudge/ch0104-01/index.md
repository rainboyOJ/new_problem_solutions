---
oj: "noi_openjudge"
problem_id: "ch0104-01"
title: "判断数正负"
description: "用 if、elif、else 覆盖正数、零和负数三个互斥区间。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/01/
---

[[TOC]]

### 题意

判断一个整数是正数、零还是负数。

### 思路

三个结果两两互斥。先判断 `number > 0`，再判断 `number == 0`，剩下的情况必为负数，适合 `if / elif / else`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

互斥分类优先用 `elif`，避免写多个独立 `if`。
