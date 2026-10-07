---
oj: "roj"
problem_id: "3505"
title: "[NOIP2001-普及]最大公约数和最小公倍数问题"
description: "x0∤y0 直接判 0；否则令 k=y0/x0，问题化为把 k 拆成互质有序对，每个质因子幂整段分配，答案 2^ω(k)。"
difficulty: "普及-"
date: 2026-10-02 04:16
updated: 2026-10-06 12:16
toc: true
tags: ["数论", "最大公约数", "质因数分解", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3505
---

[[TOC]]

## 题目描述

给定正整数 $x_0,y_0$，求有序正整数对 $(P,Q)$ 的个数，满足 $\gcd(P,Q)=x_0$ 且 $\operatorname{lcm}(P,Q)=y_0$。

输入一行两个正整数 $x_0,y_0$；输出一行一个整数表示答案。

样例：$3\ 60$ 时答案为 $4$。

## 思路

若 $x_0 \nmid y_0$ 则答案为 $0$。否则令 $k=y_0/x_0$，问题等价于把 $k$ 拆成互质有序对 $ab=k$，每个质因子幂只能整段给 $a$ 或 $b$，方案数为 $2^{\omega(k)}$。

## 参考代码

@include-code(./main.cpp, cpp)
