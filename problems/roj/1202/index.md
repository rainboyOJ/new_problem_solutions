---
oj: "roj"
problem_id: "1202"
title: "Pell数列"
description: "利用同余封闭性先递推打表到最大 k，再 O(1) 回答每组询问。"
difficulty: "入门"
date: 2026-09-29 23:15
updated: 2026-10-05 05:27
toc: true
tags:
  - 递推
  - 打表
  - 同余
favorite: false
favorite_reason: ""
categories:
  - 递推
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1202
---

[[TOC]]

## 题目描述

Pell 数列定义为 $a_1=1$，$a_2=2$，$a_n=2a_{n-1}+a_{n-2}$（$n>2$）。
输入 $n$ 组正整数 $k$（$1\leqslant k<1000000$），输出 $a_k\bmod 32767$。

## 思路

利用同余封闭性先递推打表到所有询问的最大 $k$，每组询问直接 $O(1)$ 查表输出。

## 参考代码

@include-code(./main.cpp, cpp)
