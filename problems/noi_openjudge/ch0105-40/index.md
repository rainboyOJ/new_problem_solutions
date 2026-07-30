---
oj: "noi_openjudge"
problem_id: "ch0105-40"
title: "数1的个数"
description: "枚举 1 至 n，利用字符串 count 统计每个数中数字 1 的出现次数。"
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
source: http://noi.openjudge.cn/ch0105/40/
---

[[TOC]]

### 题意

把 $1$ 到 $n$ 的所有整数写出，统计其中数字 `1` 总共出现多少次。

### 思路

数据范围只有 $10000$，逐个枚举即可。对每个数转换为字符串，`count("1")` 给出它内部数字 `1` 的出现次数，再用生成器表达式求和。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设 $n$ 的十进制位数为 $d$，时间复杂度为 $O(nd)$，额外空间复杂度为 $O(d)$。

### 总结

范围较小时，枚举每个数并统计其字符串字符数，是可靠且易读的数位统计方法。
