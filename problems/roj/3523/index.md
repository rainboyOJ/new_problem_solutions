---
oj: "roj"
problem_id: "3523"
title: "[NOIP2003-普及] 麦森数"
description: "位数用对数闭式一次算出，末 500 位用高精度快速幂模 10^500 求得。"
difficulty: "普及-"
date: 2026-10-02 05:18
updated: 2026-10-06 02:35
toc: true
tags: ["高精度", "数学", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1083"
    reason: "B 的子问题二直接复用 A 教的模意义快速幂：都是把 a^b 的指数二进制拆解、每步乘法后取模以避免构造巨大整数，A 用它求 a^b mod 7 再查星期表，B 用 pow(2,P,10^500) 求 2^P mod 10^500 得到末 500 位，再叠加 A 未涉及的对数闭式位数与补零切行流程。"
  - oj: "roj"
    problem_id: "1326"
    reason: "B 的末 500 位子问题直接复用 A 教的二进制快速幂逐步取模这一关键观察，把 b^p mod k 的模板套到 (2^P-1) mod 10^500 上，再叠加 log10 位数闭式"
  - oj: "roj"
    problem_id: "1616"
    reason: "B 的末 500 位子问题直接复用 A 教的三参数 pow 模快速幂，只是把底数换成 2、模换成 10**500"
common: []
recommend: []
source: https://roj.ac.cn/problem/3523
---

[[TOC]]

## 题目描述

给定正整数 $P$（$1000 < P \leqslant 3021377$），求 $2^P-1$ 的十进制位数，以及它的最后 500 位数字（不足 500 位时高位补 `0`，每 50 位一行输出）。

## 思路

位数由公式 $\lfloor P\log_{10}2\rfloor+1$ 直接得出。末 500 位只需计算 $(2^P-1)\bmod 10^{500}$，用高精度快速幂在 $O(\log P)$ 次模乘内完成，全程不构造完整大整数。

## 参考代码

@include-code(./main.cpp, cpp)
