---
oj: "roj"
problem_id: "1099"
title: "第n小质数"
description: "用埃拉托斯特尼筛法筛出上界内的全部质数，按升序数到第 n 个输出。"
difficulty: "入门"
date: 2026-07-06 10:30
updated: 2026-10-05 01:08
toc: true
tags:
  - 质数
  - 筛法
  - 埃拉托斯特尼筛法
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1099"
---

[[TOC]]

## 题目描述

给定一个不超过 $10000$ 的正整数 $n$，求第 $n$ 小的质数。例如质数升序为 $2,3,5,7,11,\dots$，第 $10$ 小的质数是 $29$。

**输入输出**：一行一个正整数 $n$（$n \leqslant 10000$）；输出一行，即第 $n$ 小的质数。

**样例输入**

```
10
```

**样例输出**

```
29
```

## 思路

由素数定理，第 $10000$ 个质数不超过 $105000$，先取 $L=105000$ 建埃拉托斯特尼筛：把每个质数从 $i^2$ 开始的倍数都标记为合数。筛完后按升序扫描，数到第 $n$ 个质数输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
