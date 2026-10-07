---
oj: "roj"
problem_id: "1617"
title: "转圈游戏"
description: "每轮相当于全体位置编号 +m (mod n)，用快速幂求 m·10^k mod n，一步算出答案。"
difficulty: "入门"
date: 2026-09-30 22:17
updated: 2026-10-06 01:04
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1617
---

[[TOC]]

## 题目描述

$n$ 个小伙伴（编号 $0\sim n-1$）围坐一圈，$i$ 号小伙伴初始在第 $i$ 号位置。每轮位置 $i$ 上的人顺时针走到位置 $(i+m) \bmod n$，共进行 $10^k$ 轮，求 $x$ 号小伙伴最后的位置。
输入一行四个整数 $n,m,k,x$，输出一行一个整数表示答案，数据范围 $1<n<10^6$，$0<m<n$，$0<k<10^9$。
样例输入 `10 3 4 5`，输出 `5`。

## 思路

每轮所有人做的事情相同：位置编号 $+m \pmod n$，所以 $10^k$ 轮后的位置为 $(x+m\cdot 10^k)\bmod n$。用快速幂求出 $10^k \bmod n$（$O(\log k)$），再代入取模即可，注意用 `long long`。

## 参考代码

@include-code(./main.cpp, cpp)
