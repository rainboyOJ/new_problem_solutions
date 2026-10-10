---
oj: "roj"
problem_id: "2061"
title: "usaco-4.1.1 麦香牛块"
description: "完全背包可达性筛求最大凑不出的块数：gcd 不为 1 时直接输出 0，否则在 65536 内筛出所有可表示数。"
difficulty: "普及"
date: 2026-10-01 05:43
updated: 2026-10-06 10:37
toc: true
tags:
  - 完全背包
  - 数论
  - 打表
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2061
---

[[TOC]]

## 题目描述

给定 $N$（$1 \le N \le 10$）种包装盒，第 $i$ 种可装 $b_i$（$1 \le b_i \le 256$）块麦香牛块，每种数量无限。求顾客不能买到的最大块数；若所有正整数都能买到，输出 $0$。

## 思路

先求所有盒容量的最大公约数 $g$，若 $g > 1$ 则非 $g$ 倍数的块永远买不到且无最大值，输出 $0$。若 $g = 1$，由 Frobenius 数论结论可知最大凑不出的数严格小于 $256^2 = 65536$，因此在 $[0, 65536]$ 上做一遍完全背包可达性筛，取最大的不可达数即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
