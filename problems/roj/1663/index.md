---
oj: "roj"
problem_id: "1663"
title: "「一本通 6.7 例 1」取石子游戏 1"
description: "巴什博弈：每步可取 1~K 颗，先手必胜当且仅当 N 不是 K+1 的倍数，O(1) 判定。"
difficulty: "入门"
date: 2026-10-01 00:47
updated: 2026-10-06 01:38
toc: true
tags:
  - "博弈论"
  - "数学"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1663
---

[[TOC]]

## 题目描述

有 $N$ 颗石子，两人轮流取，每步至少取 $1$ 颗、至多取 $K$ 颗，取走最后一颗者获胜，双方都采用最优策略。输入一行两个整数 $N$、$K$（$1\le N\le 10^5,\ 1\le K\le N$），先手必胜输出 `1`，后手必胜输出 `2`。样例输入 `23 3`，输出 `1`。

## 思路

这是巴什博弈：先手必败当且仅当 $N$ 是 $K+1$ 的倍数。若不是倍数，先手取走 $N \bmod (K+1)$ 颗，此后每轮都补足到 $K+1$。因此只需判断 $N \bmod (K+1)$ 是否为零，时间 $O(1)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
