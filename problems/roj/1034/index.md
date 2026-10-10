---
oj: "roj"
problem_id: "1034"
title: "计算三角形面积"
description: "平移一个顶点到原点，两向量叉积绝对值的一半即三角形面积，再用 %.2f 输出，O(1) 无开方。"
difficulty: "入门"
date: 2026-09-29 15:03
updated: 2026-10-04 23:00
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1034
---

[[TOC]]

## 题目描述

给定平面上三角形的三个顶点 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，求它的面积，精确到小数点后两位。输入一行 6 个浮点数，依次为三个顶点的坐标；输出一行一个数，即三角形面积、保留两位小数。样例输入 `0 0 4 0 0 3`，样例输出 `6.00`。

## 思路

把顶点 $A$ 平移到原点，两条边向量的叉积绝对值的一半就是面积：$S=\frac{|(x_2-x_1)(y_3-y_1)-(x_3-x_1)(y_2-y_1)|}{2}$，不用开方、没有分母。取绝对值可兼容任意顶点绕向和负坐标；输出必须用 `%.2f` 格式化，`round()` 会丢掉末尾的 0。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
