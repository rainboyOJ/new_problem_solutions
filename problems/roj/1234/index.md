---
oj: "roj"
problem_id: "1234"
title: "2011"
description: "取 n 的末四位作为指数，用快速幂求 2011^n mod 10^4。"
difficulty: "普及-"
date: 2026-09-30 00:56
updated: 2026-10-07 12:15
toc: true
tags: ["数论", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1326"
    reason: "B 的 qpow（res=res*a%mod、a=a*a%mod、e>>=1）就是 A 教的二进制分解快速幂逐位平方、位为 1 累乘这一步，只是额外叠加指数取末四位再取模的数论化简"
common: []
recommend: []
source: https://roj.ac.cn/problem/1234
---

[[TOC]]

## 题目描述

给定 $k$（$k \leq 200$）组询问，每组给一个位数不超过 $200$ 的正整数 $n$，求 $2011^n$ 的后四位（不足四位直接输出整数）。

## 思路

$2011$ 与 $10^4$ 互素，指数模 $500$ 周期；又 $500 \mid 10^4$，所以只需取 $n$ 末四位作为指数做快速幂。读入遇到 EOF 时沿用上一个数，对齐原题数据。

## 参考代码

@include-code(./main.cpp, cpp)
