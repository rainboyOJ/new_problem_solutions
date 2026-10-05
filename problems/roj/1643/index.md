---
oj: "roj"
problem_id: "1643"
title: "「一本通 6.5 例 3」Fibonacci 前 n 项和"
description: "用恒等式 S_n = f_{n+2} - 1 把前缀和化为单项，再用 2×2 转移矩阵的快速幂在 O(log n) 次矩阵乘法内求出 f_{n+2} mod m。"
difficulty: "普及"
date: 2026-09-30 23:43
updated: 2026-10-06 01:30
toc: true
tags: ["数学", "矩阵乘法", "快速幂", "斐波那契", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1643
---

[[TOC]]

## 题目描述

定义 Fibonacci 数列 $f_1 = f_2 = 1$，$f_k = f_{k-1} + f_{k-2}$。给定 $n, m$，求前 $n$ 项和 $S_n = f_1 + f_2 + \cdots + f_n \pmod m$。

输入格式：一行两个整数 $n\ m$。输出格式：一行一个整数表示 $S_n \bmod m$。

样例：输入 `5 1000`，输出 `12`。数据范围：$1 \le n \le 2 \times 10^9$，$1 \le m \le 10^9 + 10$。

## 思路

前缀和满足恒等式 $S_n = f_{n+2} - 1$，于是只需求第 $n+2$ 项。Fibonacci 是二阶线性递推，用 $2 \times 2$ 转移矩阵 $T = \begin{pmatrix}1&1\\1&0\end{pmatrix}$ 的快速幂可在 $O(\log n)$ 次乘法内得到 $f_{n+2}$，再减 1 取模即为答案。注意 C++ 中负数取模需修正。

## 参考代码

@include-code(./main.cpp, cpp)
