---
oj: "roj"
problem_id: "1291"
title: "数字组合"
description: "0/1 背包计数：ways[0]=1，ways[s] += ways[s-a[i]] 且容量倒序枚举，答案即 ways[t]，O(nt)。"
difficulty: "普及-"
date: 2026-09-30 03:41
updated: 2026-10-05 08:10
toc: true
tags:
  - "动态规划"
  - "背包问题"
  - "计数DP"
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1291
---

[[TOC]]

## 题目描述

有 $n$ 个正整数 $a_1,\dots,a_n$ 和一个目标值 $t$（$1 \leqslant n \leqslant 20$，$1 \leqslant t \leqslant 1000$），求选出若干个数使和恰为 $t$ 的组合方式数——只看选了哪些下标，选取顺序不产生新方案（$1+4$ 与 $4+1$ 是同一组合）。输入第一行是 $n$ 和 $t$，第二行是 $n$ 个正整数；输出组合方式的数目。样例：$n=5$、$t=5$、$a=(1,2,3,4,5)$，答案为 $3$，对应 $1+4$、$2+3$、$5$。

## 思路

设 `ways[s]` 为从已考虑的数中选出若干、和恰为 $s$ 的组合数，`ways[0]=1` 表示一个数都不选。每个数至多用一次，于是这是 0/1 背包的方案计数版：对每个 $a_i$ 做 `ways[s] += ways[s-a[i]]`，容量必须从 $t$ 倒序枚举，右侧读到的才是本轮更新前的旧值（读新值就变成完全背包，会重复使用同一个数）。答案为 `ways[t]`，复杂度 $O(nt)$。

## 参考代码

@include-code(./main.cpp, cpp)
