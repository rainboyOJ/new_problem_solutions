---
oj: "roj"
problem_id: "1288"
title: "三角形最佳路径问题"
description: "数字三角形经典 DP：自底向上滚动数组，O(h²) 时间求最大路径和。"
difficulty: "入门"
date: 2026-09-30 03:26
updated: 2026-10-05 08:09
toc: true
tags: ["动态规划", "数字三角形", "滚动数组"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1288
---

[[TOC]]

## 题目描述

给定一个高度为 $h$（$1 \leqslant h \leqslant 100$）的数字三角形，第 $r$ 行有 $r$ 个正整数。从顶部出发，每一步只能走到下一层正下方或右下方的数，直到最底层，求路径上数字之和的最大值。输入第一行为 $h$；接下来 $h$ 行，第 $r$ 行为该行的 $r$ 个整数，用空格分隔；输出最佳路径的数字之和。例如输入 `5`，`7`，`3 8`，`8 1 0`，`2 7 4 4`，`4 5 2 6 5` 时输出 `30`。

## 思路

设 $f(r, c)$ 表示从 $(r, c)$ 出发到底部的最大路径和，则 $f(r, c) = a(r, c) + \max(f(r+1, c), f(r+1, c+1))$，最底层 $f(h, c) = a(h, c)$，答案为 $f(1, 1)$。递推只依赖下一行，用一维数组自底向上滚动即可，时间复杂度 $O(h^2)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
