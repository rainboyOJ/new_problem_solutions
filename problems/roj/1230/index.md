---
oj: "roj"
problem_id: "1230"
title: "寻找平面上的极大点"
description: "按 x 降序、y 降序排序后一次扫描：已扫过点都满足 x' ≥ x，故当前点被支配当且仅当 y 不大于已扫过的最大 y，判定降为 O(1)，总复杂度 O(n log n)。"
difficulty: "入门"
date: 2026-09-30 00:42
updated: 2026-10-05 06:04
toc: true
tags: ["入门", "排序", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1230
---

[[TOC]]

## 题目描述

平面上有 $n$ 个互不相同的整点 $(x_i,y_i)$。若 $x \geqslant a$ 且 $y \geqslant b$，则称 $(x,y)$ **支配** $(a,b)$。要求输出所有不被其它点支配的**极大点**，按 $x$ 坐标从小到大。$n \leqslant 100$，坐标非负。

样例：$(1,2),(2,2),(3,1),(2,3),(1,4)$ 的极大点为 $(1,4),(2,3),(3,1)$。

## 思路

按 $x$ 降序、$y$ 降序排序后扫描：已扫过的点都满足 $x' \geqslant x$，所以当前点是极大点当且仅当 $y$ 大于已扫过的最大 $y$。扫描得到的点 $x$ 递减，反转即为答案顺序。注意支配允许取等，因此判断要用严格大于。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
