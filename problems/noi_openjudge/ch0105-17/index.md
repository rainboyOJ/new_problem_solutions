---
oj: "noi_openjudge"
problem_id: "ch0105-17"
title: "菲波那契数列"
description: "用两个滚动变量迭代计算第 k 个斐波那契数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["递推", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/17/
---

[[TOC]]

### 题意

数列前两项均为 1，之后每项为前两项之和，求第 $k$ 项。

### 思路

只需要保存相邻两项。每轮赋值 `first, second = second, first + second`，同时完成状态推进；位置为 1 时直接输出第一项。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(k)$，额外空间复杂度为 $O(1)$。

### 总结

线性递推若只依赖有限个前项，就用滚动变量替代整个数组。
