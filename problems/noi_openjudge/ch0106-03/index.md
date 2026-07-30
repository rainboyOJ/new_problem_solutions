---
oj: "noi_openjudge"
problem_id: "ch0106-03"
title: "计算书费"
description: "用 zip 配对十种图书单价和购买数量，求加权总价。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/03/
---

[[TOC]]

### 题意

已知十种图书的单价与购买数量，计算总书费并保留一位小数。

### 思路

将单价放在 `prices` 中。`zip(prices, counts)` 按相同位置配对单价和数量，逐项相乘后求和。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定十种图书，时间和额外空间复杂度均为 $O(1)$。

### 总结

对应位置的两组数据做加权和时，`zip` 能避免手写下标。
