---
oj: "roj"
problem_id: "1268"
title: "【例9.12】完全背包问题"
description: "完全背包模板题：容量正序枚举，同一种物品可重复选取。"
difficulty: "普及-"
date: 2026-09-30 02:38
updated: 2026-10-05 07:38
toc: true
tags:
  - "动态规划"
  - "背包问题"
  - "完全背包"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1268
---

[[TOC]]

## 题目描述

设有 $n$ 种物品，每种物品有重量 $W_i$ 和价值 $C_i$，每种物品数量无限。背包容量为 $M$，从中选取若干件物品（同一种可多次取），使总重量不超过 $M$ 且总价值最大。输入第一行为 $M$ 和 $n$，接下来 $n$ 行每行两个整数 $W_i, C_i$。输出格式为 `max=X`。

## 思路

完全背包：设 $dp[j]$ 表示容量不超过 $j$ 时的最大价值。按物品顺序处理，对第 $i$ 种物品，容量 $j$ 从 $W_i$ 到 $M$ 正序枚举，转移为 $dp[j] = \max(dp[j], dp[j-W_i] + C_i)$。正序保证 $dp[j-W_i]$ 已被本轮更新，从而同一种物品可重复选取。初始所有 $dp[j]=0$，最终输出 $dp[M]$。

## 参考代码

@include-code(./main.cpp, cpp)
