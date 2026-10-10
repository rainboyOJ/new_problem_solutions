---
oj: "roj"
problem_id: "1632"
title: "「一本通 6.4 例 2」同余方程"
description: "用扩展欧几里得求 ax + by = 1 的特解，再把 x 取模调到最小正整数解。"
difficulty: "入门"
date: 2026-09-30 23:08
updated: 2026-10-06 01:24
toc: true
tags:
  - "数论"
  - "扩展欧几里得"
  - "同余方程"
favorite: false
favorite_reason: ""
categories:
  - "数论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1632
---

[[TOC]]

## 题目描述

求同余方程 $ax \equiv 1 \pmod b$ 的最小正整数解。输入一行两个正整数 $a, b$（$2 \le a, b \le 2 \times 10^9$），保证有解；输出最小正整数解 $x_0$。样例输入 `3 10`，输出 `7`。

## 思路

$ax \equiv 1 \pmod b$ 等价于 $ax + by = 1$，因保证有解故 $\gcd(a, b) = 1$。用扩展欧几里得求出一组特解 $x$，通解为 $x + kb$，把 $x$ 取模调整到 $[1, b]$ 即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
