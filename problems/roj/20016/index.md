---
oj: "roj"
problem_id: "20016"
title: "矩形玻璃罩"
description: "x、y 两个方向独立取最小外接矩形，边界不算罩内且角点必须为整数，恰好把每条边强制外扩 1 格。"
difficulty: "入门"
date: 2026-08-28 22:10
updated: 2026-10-06 08:59
toc: true
tags: ["几何", "思维"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20016
---

[[TOC]]

## 题目描述

给定平面上的 $n$ 个点，求四边与坐标轴平行的矩形，要求所有点严格落在矩形内部（边界上的点不算），且左上角与右下角坐标都是整数，使面积最小，输出该矩形左上角与右下角的坐标。

输入：第一行整数 $n$，接下来 $n$ 行每行两个整数 $x,y$。输出：两行，分别是左上角坐标与右下角坐标。数据范围 $2 \leqslant n \leqslant 2\times10^5$，$1 \leqslant x,y \leqslant 10^8$。

样例 1 输入 `2 / 3 4 / 5 6`，输出 `2 3 / 6 7`；样例 2 输入 `5 / 44 62 / 34 69 / 24 78 / 42 44 / 64 10`，输出 `23 9 / 65 79`。

## 思路

x、y 两方向独立取极值：左边界必须小于最小 x、右边界必须大于最大 x，整数约束下最紧只能取 `minx-1`、`maxx+1`，y 方向同理，故答案为 `(minx-1, miny-1)` 到 `(maxx+1, maxy+1)`。一遍扫描维护四个极值即可，时间复杂度 O(n)。

## 参考代码

@include-code(./main.cpp, cpp)
