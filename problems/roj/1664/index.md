---
oj: "roj"
problem_id: "1664"
title: "「一本通 6.7 例 2」取石子游戏 2"
description: "Nim 博弈：把各堆石子数按位异或，先手必胜当且仅当异或和（Nim 和）非零，O(N) 判定。"
difficulty: "普及"
date: 2026-10-01 00:46
updated: 2026-10-06 01:45
toc: true
tags:
  - "博弈论"
  - "数学"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
common: []
recommend: []
source: https://roj.ac.cn/problem/1664
---

[[TOC]]

## 题目描述

有 $2$ 名玩家和 $N$ 堆石子，第 $i$ 堆有 $X_i$ 颗。双方轮流操作，每次选一个非空的堆并从中取走至少 $1$ 颗石子；轮到某人取时已没有石子可取，该人算负。两名玩家都采取最优策略，先手获胜输出 `win`，后手获胜输出 `lose`。
输入：第一行一个整数 $N$；第二行 $N$ 个空格间隔的整数 $X_i$。输出：仅一行，`win` 或 `lose`。
数据范围：$N \leqslant 5 \times 10^4$，$1 \leqslant X_i \leqslant 10^5$。样例输入 `4` 与 `7 12 9 15`，样例输出 `win`。

## 思路

这是经典 Nim 博弈，由 Bouton 定理：把 $N$ 堆石子数全部按位异或得到 Nim 和 $S$，先手必胜当且仅当 $S \neq 0$。原因是 $S \neq 0$ 时总能从最高位有 $1$ 的那一堆取石子把局面一步归零，而 $S = 0$ 时任何取法都会使异或和重新非零，必胜方由此始终把 $S = 0$ 的必败局面留给对手，于是只需一遍异或即可判定。

## 参考代码

@include-code(./main.cpp, cpp)
