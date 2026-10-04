---
oj: "roj"
problem_id: "1194"
title: "移动路线"
description: "把网格路线拆成步序列：每条路恰含 m-1 步上、n-1 步右，路线与「在总步数里选上步位置」一一对应，答案即组合数 C(m+n-2, m-1)，用 math.comb 一步求出。"
difficulty: "入门"
date: 2026-09-29 22:50
updated: 2026-10-05 05:11
toc: true
tags: ["入门", "网格", "动态规划", "组合计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1194
---

[[TOC]]

## 题目描述

X 桌子上有 $m$ 行 $n$ 列的方格矩阵，左下角为 $(1,1)$、右上角为 $(m,n)$。蚂蚁从 $(1,1)$ 出发到 $(m,n)$，每步只能向上或向右走一格，且不能离开矩阵。求不同的移动路线总数。输入一行两个整数 $m,n$（$0 < m+n \le 20$），输出方案数。$m=n=1$ 时路线数为 $1$；样例 $m=2,n=3$ 时路线数为 $3$。

## 思路

每条路线必然恰含 $m-1$ 步上、$n-1$ 步右，总步数 $m+n-2$；路线与"在这 $m+n-2$ 步里选哪几步上"一一对应，答案为组合数 $C(m+n-2, m-1)$。计算可用乘法逐步累乘，无需建 DP 表，$m=1$ 或 $n=1$ 时自动得到 $1$。

## 参考代码

@include-code(./main.cpp, cpp)