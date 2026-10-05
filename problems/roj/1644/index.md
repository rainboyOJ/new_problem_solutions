---
oj: "roj"
problem_id: "1644"
title: "「一本通 6.5 例 4」佳佳的 Fibonacci"
description: "加权 Fibonacci 和有封闭形式 T(n)=nF(n+2)-F(n+3)+2，先用快速倍增 O(log n) 求出相邻 Fibonacci 对，再一代入公式。"
difficulty: "普及"
date: 2026-09-30 23:43
updated: 2026-10-06 01:30
toc: true
tags: ["数学", "递推", "快速幂"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1644
---

[[TOC]]

## 题目描述

佳佳定义 $T(n)=(F_1+2F_2+\cdots+nF_n)\bmod m$，其中 $F_1=F_2=1,\ F_i=F_{i-1}+F_{i-2}$；给定 $n,m$ 求 $T(n)$。输入一行两个整数 $n,m$（$1\leqslant n,m\leqslant 2^{31}-1$），输出一行 $T(n)$。样例输入 `5 5`，样例输出 `1`。

## 思路

由恒等式 $T(n)=nF_{n+2}-F_{n+3}+2$，只需算出 $F_{n+2},F_{n+3}$；用快速倍增在 $O(\log n)$ 内得到相邻 Fibonacci 对，再代入公式取模。

## 参考代码

@include-code(./main.cpp, cpp)
