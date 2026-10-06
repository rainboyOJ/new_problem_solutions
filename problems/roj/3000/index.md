---
oj: "roj"
problem_id: "3000"
title: "a^b"
description: "把指数 b 按二进制拆成若干 2 的幂之和，逐位平方底数、只在为 1 的位累乘，用 O(log b) 次模乘求出 a^b mod p。"
difficulty: "普及-"
date: 2026-10-01 09:05
updated: 2026-10-06 10:43
toc: true
tags: ["数学", "位运算", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3000
---

[[TOC]]

## 题目描述

给定整数 $a, b, p$（$p \neq 0$，$0 \leqslant a, b, p \leqslant 10^9$），求 $a^b \bmod p$ 的值。输入一行三个整数 $a, b, p$，用空格隔开；输出一个整数表示结果。样例输入 `3 2 7`，输出 `2`。约定 $0^0 = 1$（即 $b = 0$ 时答案恒为 $1 \bmod p$），$p = 1$ 时答案恒为 $0$。

## 思路

把指数 $b$ 按二进制拆成若干个 2 的幂之和，则 $a^b$ 等于 $b$ 的二进制中为 1 的那些位对应的 $a^{2^k}$ 之积。这些幂可以递推：$a^{2^{k+1}} = \left(a^{2^k}\right)^2$，于是每轮只需判断当前位是否为 1、把底数乘进答案，再平方底数并右移指数，共 $O(\log b)$ 次模乘。初始化 `result = 1 % p`、`base = a % p`，$b = 0$ 与 $p = 1$ 两种边界会自动得到正确结果。

## 参考代码

@include-code(./main.cpp, cpp)
