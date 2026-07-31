---
oj: "shumeng"
problem_id: "CSP202104A"
title: "灰度直方图"
description: "扫描所有像素并累加对应灰度值的频次数组。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "计数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202104A
---

[[TOC]]

### 题意

给出灰度范围为 `[0,L)` 的图像矩阵，输出每个灰度值出现的像素数量。

### 思路

开一个长度为 `L` 的计数数组。读到灰度值 `x` 时递增 `count[x]`，最后按灰度从小到大输出。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

扫描全部 $n\times m$ 个像素，时间复杂度为 $O(nm)$，空间复杂度为 $O(L)$。

### 总结

直方图就是按值分桶的频次数组，图像行列结构不影响统计过程。
