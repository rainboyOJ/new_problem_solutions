---
oj: "shumeng"
problem_id: "CSP202104B"
title: "邻域均值"
description: "用二维前缀和快速计算每个裁剪邻域的总和，再比较均值阈值。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["前缀和", "二维前缀和", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202104B
---

[[TOC]]

### 题意

统计灰度矩阵中邻域平均值不超过阈值的像素数。边界处的邻域按图像范围裁剪。

### 思路

构造二维前缀和。对每个像素将邻域裁剪为矩形 `[top,bottom]×[left,right]`，在 $O(1)$ 时间求和。用 `sum <= threshold * area` 比较，避免浮点数。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

建表和枚举像素均为 $O(n^2)$，空间复杂度为 $O(n^2)$。

### 总结

二维前缀和把每个邻域求和从遍历正方形降为四次数组访问；边界只需裁剪矩形端点。
