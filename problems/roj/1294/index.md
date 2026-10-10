---
oj: "roj"
problem_id: "1294"
title: "Charm Bracelet"
description: "一维 0-1 背包 DP：倒序枚举容量，保证每件物品至多选一次，O(nm) 求出不超过背包容量的最大价值。"
difficulty: "入门"
date: 2026-09-30 03:39
updated: 2026-10-05 08:18
toc: true
tags: ["动态规划", "0-1 背包", "一维 DP"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1294
---

[[TOC]]

## 题目描述

有 $n$ 件物品，第 $i$ 件的重量 $w_i$、价值 $c_i$，背包容量 $m$，每件至多选一次，求总重 $\le m$ 时的最大总价值（$n\le 3500$, $m\le 12880$）。输入：第一行 $n$、$m$，接下来 $n$ 行 $w_i$、$c_i$。样例：`4 6 / 1 4 / 2 6 / 3 12 / 2 7` → `23`。

## 思路

经典 0-1 背包。设 $f[v]$ 为容量 $v$ 时的最大价值，依次处理每件物品并倒序枚举 $v$，转移 $f[v]=\max(f[v], f[v-w]+c)$，答案即 $f[m]$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
