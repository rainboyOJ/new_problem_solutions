---
oj: "noi_openjudge"
problem_id: "ch0104-20"
title: "求一元二次方程的根"
description: "按判别式正负分类输出两个实根、重根或共轭复根。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "分类讨论", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/20/
---

[[TOC]]

### 题意

求 $ax^2+bx+c=0$ 的根；按判别式输出两实根、重根或一对共轭复根，全部保留 5 位小数。

### 思路

令 $D=b^2-4ac$。$D>0$ 时计算两个实根后排序，保证 `x1>x2`；$D=0$ 时输出同一个根；$D<0$ 时实部是 $-b/(2a)$，虚部绝对值是 $\sqrt{-D}/|2a|$。输出前把 `-0.0` 规范化为 `0.0`，避免违背题面格式。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

二次方程题的主体是判别式分类；格式要求同样重要，根的顺序、符号和负零都要控制。
