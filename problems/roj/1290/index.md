---
oj: "roj"
problem_id: "1290"
title: "采药"
description: "0/1 背包裸题：dp[j] 表示时间上限 j 能采到的最大价值，容量倒序转移保证每株草药只用一次，dp[T] 即答案。"
difficulty: "入门"
date: 2026-09-30 03:38
updated: 2026-10-04 22:12
toc: true
tags:
  - "DP"
  - "01背包"
  - "动态规划"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1290
---

[[TOC]]

## 题目描述

辰辰进山洞采药，总时间上限 $T$（$1\le T\le 1000$），面前有 $M$ 株（$1\le M\le 100$），每株耗时 $\text{cost}_i$、价值 $\text{value}_i$（均在 $[1,100]$），每株至多采一次。输入第一行是 $T$、$M$，接下来 $M$ 行各给一株的 $(\text{cost}, \text{value})$，输出总时间不超过 $T$ 时能采到的最大总价值。样例：$T=70$、草药 $(71,100),(69,1),(1,2)$ → 输出 $3$。

## 思路

一维 0/1 背包：`dp[j]` 表示时间上限 $j$ 下的最大价值，初始化为 $0$；按草药顺序遍历，容量从 $T$ 倒序扫到 $\text{cost}$，令 `dp[j] = max(dp[j], dp[j - cost] + value)`，倒序保证每株只入一次；答案为 `dp[T]`。

## 参考代码

@include-code(./main.cpp, cpp)