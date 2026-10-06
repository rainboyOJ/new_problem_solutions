---
oj: "roj"
problem_id: "3576"
title: "[NOIP2010-普及] 数字统计"
description: "区间 [L,R] 中数码 2 出现次数，用前缀差按位分段 O(log R) 计数。"
difficulty: "入门"
date: 2026-10-02 08:40
updated: 2026-10-06 14:26
toc: true
tags: ["入门", "数位", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3576
---

[[TOC]]

## 题目描述

给定区间 $[L, R]$，统计其中所有整数的十进制表示里数码 $2$ 出现的总次数。$1 \le L \le R \le 100000$。

## 思路

设 $f(n)$ 为 $[0,n]$ 中数码 $2$ 的出现次数，答案为 $f(R)-f(L-1)$。对每一位把 $n$ 分成高位、当前位、低位三段：前缀小于高位时贡献 `高位×权重`，前缀等于高位时按当前位与 $2$ 的大小补 `权重 / 低位+1 / 0`。

## 参考代码

@include-code(./main.cpp, cpp)
