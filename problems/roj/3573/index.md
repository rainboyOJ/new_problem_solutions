---
oj: "roj"
problem_id: "3573"
title: "[NOIP2009-提高] Hankson的趣味题"
description: "由 gcd 与 lcm 条件推出 x 必是 b1 的约数，用试除 O(√b1) 枚举候选并通过三个 gcd 判定统计合法 x 的个数。"
difficulty: "普及-"
date: 2026-10-02 08:25
updated: 2026-10-06 14:26
toc: true
tags: [数学, gcd, 约数枚举]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3573
---

[[TOC]]

## 题目描述

Hankson 在思考 gcd/lcm 的"逆问题"：给定正整数 $a_0,a_1,b_0,b_1$（保证 $a_1\mid a_0$，$b_0\mid b_1$），统计满足 $\gcd(x,a_0)=a_1$ 且 $\operatorname{lcm}(x,b_0)=b_1$ 的正整数 $x$ 的个数；不存在则答案为 $0$。输入第一行为正整数 $n$，接下来 $n$ 行每行四个正整数 $a_0,a_1,b_0,b_1$（$1\leqslant a_0,a_1,b_0,b_1\leqslant 2\times 10^9$，$n\leqslant 2000$）；输出共 $n$ 行，每行即满足条件的 $x$ 的个数（不存在输出 $0$）。例如输入三行 `2`、`41 1 96 288`、`95 1 37 1776`，输出两行 `6`、`2`。

## 思路

由条件一知 $a_1\mid x$，由条件二知 $x\mid b_1$，所以合法的 $x$ 只能是 $b_1$ 的约数。对 $b_1$ 做 $O(\sqrt{b_1})$ 试除枚举每个约数 $d$，依次验证 $d\bmod a_1=0$、$\gcd(d,a_0)=a_1$、以及乘积等式 $d\cdot b_0=b_1\cdot\gcd(d,b_0)$（等价于 $\operatorname{lcm}(d,b_0)=b_1$），全部通过就计数。

## 参考代码

@include-code(./main.cpp, cpp)
