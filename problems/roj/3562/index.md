---
oj: "roj"
problem_id: "3562"
title: "传球游戏"
description: "环上传球计数：设 f(i,j) 为传 i 次后球在 j 手中的方案数，每步只能从左右邻居转移，答案 f(m,0)，O(mn) 递推。"
difficulty: "普及"
date: 2026-10-02 07:48
updated: 2026-10-06 14:05
toc: true
tags: ["动态规划", "计数", "环"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3562
---

[[TOC]]

## 题目描述

$n$ 个同学围成一圈，编号 $0 \sim n-1$（小蛮为 $0$ 号）。球最初在 $0$ 号手中，每次必须传给左右相邻同学之一。求恰好传 $m$ 次后球回到 $0$ 号手中的方案数。

输入格式：一行两个整数 $n, m$（$3 \le n \le 30, 1 \le m \le 30$）。

输出格式：一个整数，表示方案数。

样例输入：`3 3`，样例输出：`2`。

## 思路

设 $f(i, j)$ 为传 $i$ 次后球在 $j$ 号手中的方案数，则 $f(i, j) = f(i-1, (j-1) \bmod n) + f(i-1, (j+1) \bmod n)$，边界 $f(0, 0) = 1$，答案 $f(m, 0)$。直接按次数逐层递推即可。

## 参考代码

@include-code(./main.cpp, cpp)
