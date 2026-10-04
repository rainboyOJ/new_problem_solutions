---
oj: "roj"
problem_id: "1196"
title: "踩方格"
description: "把落点压成「本行只有一格」和「本行已横走成段」两类，按 3 种/2 种续走做线性递推。"
difficulty: "普及-"
date: 2026-09-29 23:04
updated: 2026-10-05 05:18
toc: true
tags: ["递推", "动态规划", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1196
---

[[TOC]]

## 题目描述

在无穷大的方格矩阵上从某点出发走 $n$ 步：每步走到相邻方格，只能向北、东、西三个方向走（不能向南），走过的格子立即塌陷、不能再走第二次；两种走法只要有一步不一样就算不同方案，求方案总数。

输入一个整数 $n$（$n \leqslant 20$），输出方案数量。样例：输入 `2`，输出 `7`。

## 思路

没有向南的走法，落点所在的最高一行只能被横走成一段连续区间，且落点是这段区间的端点。把落点压成两类：本行只有落点一格（可走北/东/西共 3 种）、本行已横走成段（只剩向北 + 唯一一侧横走共 2 种），线性递推 $a_k = a_{k-1} + b_{k-1}$、$b_k = 2a_{k-1} + b_{k-1}$，答案 $f_n = a_n + b_n$（初值 $a_0=1, b_0=0$，得 $f_2=7$）。

## 参考代码

@include-code(./main.cpp, cpp)
