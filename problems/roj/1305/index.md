---
oj: "roj"
problem_id: "1305"
title: "Maximum sum"
description: "枚举分界 k，左侧前缀最大子段和与右侧后缀最大子段和相加，O(n)。"
difficulty: "普及"
date: 2026-09-30 04:10
updated: 2026-10-05 08:50
toc: true
tags: ["动态规划", "最大子段和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1305
---

[[TOC]]

## 题目描述

给定长度为 $n$（$2 \leqslant n \leqslant 50000$）的整数序列，求两个不重合连续子段的和的最大值。$T$ 组数据。

## 思路

两段不相交等价于存在分界 $k$，左段落在 $a[1..k]$，右段落在 $a[k+1..n]$。正向求前缀最大子段和 $g[k]$，反向求后缀最大子段和 $h[k+1]$，答案为 $\max_{1 \leqslant k < n}(g[k] + h[k+1])$。

## 参考代码

@include-code(./main.cpp, cpp)

