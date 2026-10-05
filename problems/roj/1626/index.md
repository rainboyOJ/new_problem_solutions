---
oj: "roj"
problem_id: "1626"
title: "「一本通 6.3 例 2」Hankson 的趣味题"
description: "由 lcm(x,b0)=b1 得 x 必整除 b1，枚举 b1 的约数并验证 gcd 与 lcm 两个条件即可计数。"
difficulty: "普及-"
date: 2026-09-30 22:55
updated: 2026-10-06 01:25
toc: true
tags: ["数论", "最大公约数", "最小公倍数", "质因数分解", "约数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1626
---

[[TOC]]

## 题目描述

给定正整数 $a_0,a_1,b_0,b_1$，求满足

$$\gcd(x,a_0)=a_1,\qquad \operatorname{lcm}(x,b_0)=b_1$$

的正整数 $x$ 的个数。其中 $1 \leqslant a_0,a_1,b_0,b_1 \leqslant 2\times 10^9$，$n \leqslant 2000$ 组询问；输入保证 $a_1 \mid a_0$ 且 $b_0 \mid b_1$。

## 思路

由 $\operatorname{lcm}(x,b_0)=b_1$ 可知 $x$ 必为 $b_1$ 的约数，因此只需枚举 $b_1$ 的所有约数（2e9 以内最多一千多个），再逐个验证 $\gcd(x,a_0)=a_1$ 与 $\operatorname{lcm}(x,b_0)=b_1$ 是否同时成立。

## 参考代码

@include-code(./main.cpp, cpp)
