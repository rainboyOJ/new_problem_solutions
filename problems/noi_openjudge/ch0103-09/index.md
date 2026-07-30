---
oj: "noi_openjudge"
problem_id: "ch0103-09"
title: "与圆相关的计算"
description: "按指定 pi 计算圆的直径、周长和面积并统一保留四位小数。"
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
source: http://noi.openjudge.cn/ch0103/09/
---

[[TOC]]

### 题意

给出半径 $r$，使用题目指定的 $\pi=3.14159$ 输出直径、周长和面积。

### 思路

三项依次是 $2r$、$2\pi r$、$\pi r^2$。不要替换为 `math.pi`，题目明确指定了近似值；三个表达式都用 `.4f`，再用空格拼成一行。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

OJ 题目给定常量时应使用给定值，哪怕标准库有更精确的常量。
