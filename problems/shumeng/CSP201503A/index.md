---
oj: "shumeng"
problem_id: "CSP201503A"
title: "图像旋转"
description: "按原矩阵从右到左的列顺序逐列输出，完成逆时针旋转 90 度。"
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
source: https://oj.shumeng.tech/p/CSP201503A
---

[[TOC]]

### 题意

给定一个 $n\times m$ 矩阵，输出其逆时针旋转 $90^\circ$ 后的 $m\times n$ 矩阵。

### 思路

先看显式构造旋转后矩阵的写法：

@include-code(./brute.cpp, cpp)

原矩阵的最右列会成为答案第一行，且列内从上到下的顺序不变。因此读入后让列号从 `m-1` 降到 `0`，每一列按行号从 `0` 到 `n-1` 输出即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(nm)$，空间复杂度为 $O(nm)$。

### 总结

矩阵旋转不必移动元素，只要确定输出的一行来自原矩阵的哪一列。逆时针旋转就是从右到左依次读取原矩阵各列。
