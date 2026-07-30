---
oj: "noi_openjudge"
problem_id: "ch0107-02"
title: "找第一个只出现一次的字符"
description: "用 Counter 统计字符频率后按原顺序找第一个频率为一的字符。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/02/
---

[[TOC]]

### 题意

找出小写字符串中第一个只出现一次的字符，没有则输出 `no`。

### 思路

先用 `Counter` 统计频率，再按原字符串顺序寻找频率为 $1$ 的字符，才能保证“第一个”。`next(..., "no")` 在找不到时给出默认结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，频次表使用 $O(n)$ 空间。

### 总结

先统计、再按原顺序扫描，是“第一个满足频率条件元素”的通用做法。
