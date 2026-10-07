---
oj: "roj"
problem_id: "3608"
title: "[NOIP2013-提高]转圈游戏"
description: "每轮所有人整体顺时针平移 m 格，10^k 轮后位置为 (x + m·10^k) mod n；只需 10^k mod n，用快速幂在 O(log k) 内求出。"
difficulty: "普及-"
date: 2026-10-02 10:17
updated: 2026-10-07 12:15
toc: true
tags: ["快速幂", "数学", "取模", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1083"
    reason: "B 直接复用 A 教的取模快速幂：A 用边乘边取模求 a^b mod 7，B 用同一算法求 10^k mod n 再算 (x+m·10^k) mod n，只是多加了环上位移可叠加的观察"
common: []
recommend: []
source: https://roj.ac.cn/problem/3608
---

[[TOC]]

## 题目描述

$n$ 个小伙伴编号 $0 \sim n-1$ 顺时针围坐一圈，初始 $i$ 号小伙伴在 $i$ 号位置。每一轮所有人同时顺时针平移 $m$ 格，共进行 $10^k$ 轮，求 $x$ 号小伙伴最终所在的位置编号。输入一行四个整数 $n, m, k, x$，输出一个整数表示位置。数据范围：$0 < n < 10^6$，$0 < m < n$，$1 \leqslant x < n$，$0 < k < 10^9$。样例输入 `10 3 4 5`，输出 `5`。

## 思路

每轮所有人整体平移 $m$ 格，所以 $10^k$ 轮后位置为 $(x + m \cdot 10^k) \bmod n$；位置只在 $0 \sim n-1$ 之间循环，因此只需 $10^k \bmod n$，用快速幂在 $O(\log k)$ 内求出即可。

## 参考代码

@include-code(./main.cpp, cpp)
