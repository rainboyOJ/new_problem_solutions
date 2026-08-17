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

## 形式化题目

给出一幅 $n\times m$ 的灰度图像，每个像素的灰度值为 $[0,L)$ 内的整数。统计每个灰度值 $x$ 出现的像素数量，输出长度为 $L$ 的直方图 $h_0,h_1,\dots,h_{L-1}$。

## 思路

直方图就是按灰度值分桶的频次数组。

### 统计步骤

1. 开一个长度为 $L$ 的计数数组；
2. 读到灰度值 $x$ 时执行 `count[x]++`；
3. 最后按灰度从小到大输出每个桶的计数。

图像的二维结构不影响统计过程，逐像素读入并累加即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

扫描全部 $n\times m$ 个像素，时间复杂度为 $O(nm)$，空间复杂度为 $O(L)$。

## 总结

直方图就是按值分桶的频次数组，图像行列结构不影响统计过程。