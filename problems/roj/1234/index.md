---
oj: "roj"
problem_id: "1234"
title: "2011"
description: "取 n 的末四位作为指数，用快速幂求 2011^n mod 10^4。"
difficulty: "普及-"
date: 2026-09-30 00:56
updated: 2026-10-05 06:12
toc: true
tags: ["数论", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
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
