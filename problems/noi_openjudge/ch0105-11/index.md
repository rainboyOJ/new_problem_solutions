---
oj: "noi_openjudge"
problem_id: "ch0105-11"
title: "整数的个数"
description: "读入序列后分别统计 1、5、10 的出现次数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["统计", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/11/
---

[[TOC]]

### 题意

给定 $k$ 个 1 到 10 的整数，分别输出 1、5、10 出现的次数。

### 思路

读成列表后，`numbers.count(value)` 返回指定值出现次数。只统计三个固定目标，分别调用 `count` 很直观。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每次 `count` 扫描序列，三次统计的时间复杂度仍为 $O(k)$，额外空间复杂度为 $O(k)$。

### 总结

目标值数量很少时，列表的 `count` 是清晰的直接解法。
