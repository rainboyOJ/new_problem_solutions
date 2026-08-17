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

## 形式化题目

给定一个 $n\times m$ 的矩阵，将其**逆时针旋转 $90^\circ$**，输出旋转后 $m\times n$ 的矩阵。

## 思路

先看显式构造旋转后矩阵的写法：

@include-code(./brute.cpp, cpp)

`brute.cpp` 里用一个新矩阵记录旋转结果：原矩阵 $(row, column)$ 的元素移动到旋转后矩阵的 $(m-1-column, row)$ 位置，最后按行输出。这个版本最贴近直觉，适合作为小数据基准。

**关键观察**：逆时针旋转 $90^\circ$ 后，答案的每一行恰好对应原矩阵的**某一列**：

- 原矩阵的最右列成为答案的第一行；
- 列内从上到下的顺序保持不变。

因此不需要真的移动元素，读入原矩阵后，让列号从 `m-1` 降到 `0`，每一列按行号从 `0` 到 `n-1` 输出即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：每个元素只输出一次，$O(nm)$。
- 空间：存储原矩阵，$O(nm)$。

## 总结

矩阵旋转不必移动元素，只要确定“输出的一行来自原矩阵的哪一列”。逆时针旋转就是从右到左依次读取原矩阵的各列，本题是这类坐标映射模拟题的起点。