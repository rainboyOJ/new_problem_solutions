---
oj: "roj"
problem_id: "1620"
title: "「一本通 6.2 练习 1」质因数分解"
description: "n 恰为两个不同质数之积，较小质因数必不超过 √n，从 2 试除到 ⌊√n⌋ 命中后用 n 除以它即得较大质数。"
difficulty: "普及-"
date: 2026-09-30 22:30
updated: 2026-10-06 01:22
toc: true
tags: ["数论", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1620
---

[[TOC]]

## 题目描述

给定正整数 $n = p \cdot q$（$p, q$ 为不同质数），求 $\max(p, q)$。

## 思路

两个质因数中小的那个必不超过 $\sqrt n$（否则乘积超过 $n$），从小到大试除 $2 \sim \lfloor\sqrt n\rfloor$，第一个整除 $n$ 的 $d$ 对应的商 $n/d$ 就是较大的质因数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
