---
oj: "roj"
problem_id: "10028"
title: "gap"
description: "线性筛出 10⁶ 内全部素数后扫一遍相邻素对，把每段 gap 里的合数统一登记为该段宽度，单点 O(1) 查表。"
difficulty: "入门"
date: 2026-10-02 19:08
updated: 2026-10-04 22:17
toc: true
tags: ["数论", "素数", "筛法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10028
---

[[TOC]]

## 题目描述

给定正整数 $N$（$N \leqslant 10^6$）。把不小于 2 的素数从小到大记为 $p_1=2,p_2=3,p_3=5,\dots$，约定素数间距 $g_i=p_{i+1}-p_i$：若 $p_i<N<p_{i+1}$ 则输出 $g_i$，特别地，若 $N$ 本身是素数则输出 $0$。输入一行一个正整数 $N$，输出一行一个整数表示答案。样例输入 `10`，样例输出 `4`（$10$ 夹在素数 $7$ 与 $11$ 之间，间隔 $11-7=4$）。

## 思路

答案只由 $N$ 落在哪一对相邻素数之间决定：同一段 gap 里的合数共享宽度 $p_{i+1}-p_i$，而 $N$ 本身是素数时为 $0$。于是用线性筛（欧拉筛）升序筛出素数，再扫一遍相邻素对，把区间内每个合数的答案统一登记，询问时直接查表。注意 $N=10^6$ 右侧的第一个素数是 $1000003$，筛表要外扩一点才能给它登记答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
