---
oj: "shumeng"
problem_id: "CSP201412B"
title: "Z 字形扫描"
description: "按副对角线 i+j 分组，并根据对角线编号奇偶交替反向输出。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "二维数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201412B
---

[[TOC]]

### 题意

给定一个 $n\times n$ 矩阵，按照 Z 字形遍历顺序输出全部元素。

### 思路

先看逐条对角线收集再输出的做法：

@include-code(./brute.cpp, cpp)

同一条左下到右上的副对角线满足 `row + column = sum`。依次处理 `sum=0..2n-2`：偶数从下向上输出，奇数从上向下输出。

4×4 矩阵的输出序号如下，编号相同的格子属于同一条副对角线：

| 0 | 2 | 6 | 7 |
| ---: | ---: | ---: | ---: |
| 1 | 5 | 8 | 13 |
| 3 | 9 | 12 | 14 |
| 4 | 10 | 11 | 15 |

每条对角线内部方向交替，边界对角线自然只有一个元素。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个矩阵元素只访问一次，时间复杂度为 $O(n^2)$；保存矩阵需要 $O(n^2)$ 空间。

### 总结

Z 字形扫描的本质是“按副对角线分组，再交替反转”。先确定对角线编号和边界，再处理方向，就不会在边缘位置上写出复杂的移动模拟。
