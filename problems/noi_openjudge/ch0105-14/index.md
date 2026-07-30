---
oj: "noi_openjudge"
problem_id: "ch0105-14"
title: "人口增长问题"
description: "按每年 0.1% 的复利增长，用 x*1.001^n 计算人口。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/14/
---

[[TOC]]

### 题意

人口基数为 $x$ 亿，每年增长 0.1%，求 $n$ 年后的人口，保留四位小数。

### 思路

每年乘以 $1.001$，连续 $n$ 年的结果为 $x\times1.001^n$。Python 的 `**` 直接表达乘方，最后使用 `.4f`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

使用内建幂运算，额外空间复杂度为 $O(1)$。

### 总结

固定增长率连续复利可写成“初值乘增长因子的年数次方”。
