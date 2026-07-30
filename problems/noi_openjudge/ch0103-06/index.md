---
oj: "noi_openjudge"
problem_id: "ch0103-06"
title: "甲流疫情死亡率"
description: "用死亡数除以确诊数并乘 100，按 .3f 输出百分率。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/06/
---

[[TOC]]

### 题意

给出确诊数和死亡数，输出死亡率百分数，保留 3 位小数。

### 思路

死亡率为 $\frac{deaths}{confirmed}\times100\%$。Python `/` 会得到浮点数，再用 `.3f` 固定三位小数；百分号是普通字符，直接写在 f-string 末尾。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

比例题先确认分子和分母的含义，再决定是否需要乘 $100$ 输出百分数。
