---
oj: "roj"
problem_id: "1301"
title: "大盗阿福"
description: "线性 DP：f[i] 表示前 i 家店铺的最大收益，每家店铺选或不选，转移时保证相邻两家不同时选。"
difficulty: "入门"
date: 2026-09-30 03:53
updated: 2026-10-05 08:33
toc: true
tags:
  - 动态规划
  - 线性 DP
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1301
---

[[TOC]]

## 题目描述

一条街有 $N$ 家店铺，每家有一定现金。阿福要洗劫其中若干家，但**不能同时洗劫相邻两家**，否则报警。求最多能拿到的现金。

输入第一行为整数 $T$（$T\le 50$），表示数据组数。每组数据第一行为 $N$（$1\le N\le 100\,000$），第二行为 $N$ 个不超过 $1000$ 的正整数。

对每组数据输出一行最大现金数。

样例输入：

```
2
3
1 8 2
4
10 7 6 14
```

样例输出：

```
8
24
```

## 思路

设 $f[i]$ 为前 $i$ 家店铺的最大收益。第 $i$ 家可以不选，则 $f[i]=f[i-1]$；可以选，则第 $i-1$ 家不能选，$f[i]=f[i-2]+a_i$。转移方程 $f[i]=\max(f[i-1],f[i-2]+a_i)$，用两个变量滚动即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
