---
oj: "noi_openjudge"
problem_id: "ch0105-34"
title: "求阶乘的和"
description: "递推维护当前阶乘并累加，求 1! 到 n! 的和。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "数学", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/34/
---

[[TOC]]

### 题意

求 $1!+2!+\cdots+n!$。

### 思路

不必每次从头计算阶乘。若 `factorial` 已经是 $(i-1)!$，乘上 $i$ 就得到 $i!$；把它加入 `total` 后继续下一轮即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

相邻阶乘只差一次乘法，维护递推值比重复计算更清晰也更高效。
