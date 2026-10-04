---
oj: "roj"
problem_id: "1207"
title: "求最大公约数问题"
description: "用辗转相除法求最大公约数：反复把 (a, b) 换成 (b, a mod b)，公因数集合始终不变而第二个数严格变小，b 归零时 a 就是答案。"
difficulty: "普及-"
date: 2026-09-29 23:37
updated: 2026-10-05 05:32
toc: true
tags: ["数论", "gcd", "辗转相除法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1207
---

[[TOC]]

## 题目描述

给定两个正整数 $a, b$（$1 \leqslant a, b < 10^9$），求它们的最大公约数。一行读入两个正整数，输出一个正整数即为答案。

样例输入：`6 9`，样例输出：`3`。

## 思路

用辗转相除法：循环把 $(a, b)$ 替换为 $(b, a \bmod b)$，公因数集合不变而 $b$ 严格减小；$b=0$ 时直接输出 $a$。复杂度 $O(\log \min(a, b))$。

## 参考代码

@include-code(./main.cpp, cpp)