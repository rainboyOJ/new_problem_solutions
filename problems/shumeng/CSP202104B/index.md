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

## 形式化题目

给出一幅 $n\times n$ 的灰度矩阵，值域为 $[0,L)$。对每个像素，其邻域是满足 $|x-i|\le r$ 且 $|y-j|\le r$ 的像素集合（越界部分裁剪掉）。统计邻域平均值不超过阈值 $t$ 的像素个数。

## 思路

朴素做法是对每个像素遍历整个邻域求和，复杂度为 $O(n^2r^2)$。用二维前缀和可以把每个邻域的求和降为 $O(1)$。

### 二维前缀和

$sum[i][j]$ 表示以 $(1,1)$ 到 $(i,j)$ 为对角矩形的像素总和，递推式为

$$
sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+A[i][j]。
$$

### 判断较暗区域

1. 对像素 $(i,j)$，把邻域裁剪成矩形 $[top,bottom]\times[left,right]$；
2. 用前缀和 $O(1)$ 求矩形内的总和与格子个数；
3. 用 $sum\le t\times count$ 比较，避免浮点误差。

先看一个直接枚举邻域格子的朴素解：

@include-code(./brute.cpp, cpp)

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

建表和枚举像素均为 $O(n^2)$，空间复杂度为 $O(n^2)$。

## 总结

二维前缀和把每个邻域求和从遍历正方形降为四次数组访问；边界只需裁剪矩形端点。