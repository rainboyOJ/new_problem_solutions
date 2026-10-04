---
oj: "roj"
problem_id: "1189"
title: "Pell数列"
description: "Pell 数列取模：预计算到最大下标后 O(1) 查表。"
difficulty: "入门"
date: 2026-09-29 22:55
updated: 2026-10-05 04:48
toc: true
tags: ["入门", "递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1189
---

[[TOC]]

## 题目描述

Pell 数列：$a_1 = 1$，$a_2 = 2$，$a_k = 2a_{k-1} + a_{k-2}$（$k > 2$）。

输入 $n$ 组正整数 $k$（$1 \le k < 10^6$），输出 $a_k \bmod 32767$。

样例输入 `2 1 8`，样例输出 `1 408`。

## 思路

先读入所有询问求出最大下标 $k_{\max}$，一次线性递推预计算到 $k_{\max}$ 并把每步对 $32767$ 取模的结果存入数组，之后每个询问直接查表输出。

## 参考代码

@include-code(./main.cpp, cpp)
