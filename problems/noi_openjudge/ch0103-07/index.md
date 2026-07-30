---
oj: "noi_openjudge"
problem_id: "ch0103-07"
title: "计算多项式的值"
description: "用 Horner 形式计算三次多项式并保留七位小数。"
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
source: http://noi.openjudge.cn/ch0103/07/
---

[[TOC]]

### 题意

给出 $x,a,b,c,d$，计算 $ax^3+bx^2+cx+d$，保留 7 位小数。

### 思路

把式子改写成 $((ax+b)x+c)x+d$。这就是 Horner 形式，按从左到右的三次乘加完成计算，避免手写多个 `x*x` 并让系数顺序更清楚。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

多项式次数固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

多项式求值优先改写为 Horner 形式：少乘法，且更容易从代码看出系数顺序。
