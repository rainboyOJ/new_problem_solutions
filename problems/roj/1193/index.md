---
oj: "roj"
problem_id: "1193"
title: "吃糖果"
description: "用 Fibonacci 递推计数：每天吃掉 1 或 2 块，f[i]=f[i-1]+f[i-2]，滚动变量 O(1) 空间实现。"
difficulty: "入门"
date: 2026-09-29 22:51
updated: 2026-10-05 05:11
toc: true
tags:
  - "递推"
  - "Fibonacci"
  - "入门"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1193
---

[[TOC]]

## 题目描述

名名有 $N$ 块巧克力（$0 < N < 20$），每天可以吃 $1$ 块或 $2$ 块。问有多少种不同的吃完方案。

### 输入格式

输入一行，整数 $N$。

### 输出格式

输出一行，方案数。

### 样例输入

```
4
```

### 样例输出

```
5
```

## 思路

设 $f[i]$ 为吃完 $i$ 块的方案数。最后一天吃 $1$ 块则前面有 $f[i-1]$ 种方案，吃 $2$ 块则有 $f[i-2]$ 种，于是 $f[i] = f[i-1] + f[i-2]$，初始 $f[0] = f[1] = 1$。用两个变量滚动递推即可。

## 参考代码

@include-code(./main.cpp, cpp)
