---
oj: "roj"
problem_id: "1165"
title: "Hermite多项式"
description: "按题面二阶递推式记忆化递归求 Hermite 多项式，结果补两位小数输出。"
difficulty: "入门"
date: 2026-09-29 21:38
updated: 2026-10-05 04:05
toc: true
tags: ["数学", "递推", "递归", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1165
---

[[TOC]]

## 题目描述

用递归的方法求 Hermite 多项式的值：

$$h_n(x)=\begin{cases}1 & n=0 \\ 2x & n=1 \\ 2x h_{n-1}(x)-2(n-1)h_{n-2}(x) & n>1\end{cases}$$

给定正整数 $n$ 和整数 $x$，求 $h_n(x)$ 的值。数据范围 $1 \le n \le 10$，$1 \le x \le 10$。

输入：两个数 $n$ 和 $x$。输出：多项式的值，保留两位小数。

样例输入：`1 2`，样例输出：`4.00`。

## 思路

按递推式递归计算，用 `memo` 数组记录每个 $h_k(x)$ 避免重复子问题。结果必为整数，直接补 `.00` 输出即可避开浮点误差。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
