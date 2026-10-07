---
oj: "roj"
problem_id: "1370"
title: "最小函数值(minval)"
description: "n 个系数全正的二次函数在正整数点上严格递增，每个函数只暴露当前最小候选 F_i(x)，用小根堆做 n 路归并，弹 m 次堆顶即为前 m 小函数值。"
difficulty: "普及-"
date: 2026-09-30 07:28
updated: 2026-10-05 12:14
toc: true
tags: ["堆", "多路归并", "python"]
favorite: false
favorite_reason: ""
categories: ["数据结构"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1370
---

[[TOC]]

## 题目描述

给定 $n$ 个二次函数 $F_i(x)=A_ix^2+B_ix+C_i$（$x\in\mathbb{N}^*$，系数均为正整数，$A_i\le 10$、$B_i\le 100$、$C_i\le 10^4$），求所有函数值中最小的 $m$ 个（重复值按多次输出），$1\le n,m\le 10^4$。输入第一行 $n,m$，随后 $n$ 行每行 $A_i,B_i,C_i$；输出一行 $m$ 个空格隔开的数。样例输入 `3 10` 与三行 `4 5 3`、`3 4 5`、`1 7 1`，输出 `9 12 12 19 25 29 31 44 45 54`。

## 思路

系数全为正，故 $F_i(x+1)-F_i(x)=A_i(2x+1)+B_i>0$，每个函数在 $x\ge 1$ 上严格递增，可把其自变量序列看成一条有序链。于是问题变成 $n$ 条有序链归并取前 $m$ 项：小根堆里放每条链的当前候选 $F_i(1)$，弹出 $m$ 次堆顶即为答案，每次弹出后把该函数的 $F_i(x+1)$ 压回堆。堆中最多 $n$ 个元素，时间复杂度 $O((n+m)\log n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
