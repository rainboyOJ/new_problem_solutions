---
oj: "roj"
problem_id: "3029"
title: "「To the Max」 最大的和"
description: "枚举上下边界把二维最大子矩阵压成一维竖条和，用列前缀和加速求和，再用 Kadane 算法求最大子段和，总复杂度 O(N^3)。"
difficulty: "普及"
date: 2026-10-01 11:03
updated: 2026-10-07 13:50
toc: true
tags: ["贪心", "前缀和", "最大子段和"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P8218"
    reason: "B 正解把 A 教的「前缀和相减得到一段区间和」直接搬成列前缀和差分 O(1) 取竖条和，再叠加二维降维与 Kadane。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3029
---

[[TOC]]

## 题目描述

给定 $n \times n$ 整数矩阵（$n \le 100$），求元素和最大的子矩阵的和。

## 思路

枚举子矩阵的上下边界行，把中间各行按列求和压成一维数组，对一维数组跑 Kadane 最大子段和，取所有上下边界组合的最大值，$O(n^3)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
