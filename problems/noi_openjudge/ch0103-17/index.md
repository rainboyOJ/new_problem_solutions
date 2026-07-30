---
oj: "noi_openjudge"
problem_id: "ch0103-17"
title: "计算三角形面积"
description: "使用鞋带公式计算三点三角形面积并取绝对值。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "几何", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/17/
---

[[TOC]]

### 题意

输入三角形三个顶点坐标，输出面积，保留 2 位小数。

### 思路

鞋带公式给出两倍有向面积：$x_1y_2+x_2y_3+x_3y_1-x_1y_3-x_2y_1-x_3y_2$。顶点顺逆时针会改变符号，面积必须非负，因此取绝对值后除以 2。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

坐标面积公式算出的是有向面积；求几何面积时别遗漏 `abs`。
