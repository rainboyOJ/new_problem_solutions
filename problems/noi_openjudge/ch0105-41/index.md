---
oj: "noi_openjudge"
problem_id: "ch0105-41"
title: "数字统计"
description: "枚举闭区间 [L,R]，用字符串 count 累加数字 2 的出现次数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["枚举", "字符串", "数位", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/41/
---

[[TOC]]

### 题意

统计闭区间 $[L,R]$ 中的所有整数里，数字 `2` 出现的总次数。

### 思路

遍历 `range(left, right + 1)`，端点 `right + 1` 保证右端点被包含。每个数转为字符串后，`count("2")` 统计本数贡献，最后累加。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设区间长度为 $s$、其中数的位数最多为 $d$，时间复杂度为 $O(sd)$，额外空间复杂度为 $O(d)$。

### 总结

计数区间题先确认是闭区间，再把右端点加一传给 Python 的 `range`。
