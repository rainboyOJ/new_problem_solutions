---
oj: "roj"
problem_id: "3512"
title: "[NOIP2002-普及]级数求和"
description: "利用调和级数严格递增且发散，从 1 开始逐项累加 1/n，部分和第一次超过 K 时的 n 即为答案，最大 K=15 也只需约 3×10^6 次加法。"
difficulty: "入门"
date: 2026-10-02 04:40
updated: 2026-10-06 12:31
toc: true
tags: ["模拟", "数学", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3512
---

[[TOC]]

## 题目描述

已知 $S_n = 1 + \frac12 + \frac13 + \dots + \frac1n$。给定整数 $K$（$1 \le K \le 15$），求最小的正整数 $n$ 使得 $S_n > K$。

**输入格式**：一个正整数 $K$  
**输出格式**：一个正整数 $n$

**样例输入**：`1`  
**样例输出**：`2`

## 思路

调和级数严格递增且发散，直接从 $n=1$ 开始逐项累加 $\frac1n$，维护部分和 $s$，当 $s > K$ 时当前的 $n$ 即为答案。$K \le 15$ 时答案不超过约 $3.3 \times 10^6$，直接模拟即可通过。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
