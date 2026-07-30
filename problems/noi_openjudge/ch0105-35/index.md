---
oj: "noi_openjudge"
problem_id: "ch0105-35"
title: "求出e的值"
description: "递推计算阶乘倒数并累加，得到截断的 e 级数近似值。"
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
source: http://noi.openjudge.cn/ch0105/35/
---

[[TOC]]

### 题意

根据 $e=1+1/1!+1/2!+\cdots+1/n!$ 计算近似值，并输出十位小数。

### 思路

初始和为常数项 $1$。循环中递推当前的 `factorial`，再加入 `1 / factorial`。最后使用 `f"{total:.10f}"` 按题意固定保留十位小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

同一个阶乘递推既可用于整数和，也可用于它的倒数级数。
