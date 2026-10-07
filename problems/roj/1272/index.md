---
oj: "roj"
problem_id: "1272"
title: "【例9.16】分组背包"
description: "外层枚举组、容量倒序、内层枚举组内物品，容量倒序保证每轮只读上一组的旧值，同组物品不会叠加。"
difficulty: "普及-"
date: 2026-09-30 02:50
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "背包", "分组背包"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "U661988"
    reason: "B 的分组背包直接复用 A 讲的「容量倒序读不到当前物品」这一具体判定：main.cpp 里 cap 从 V 递减，使 dp[cap-W_j] 只含上一组的旧值，从而同组物品不在同一格叠加、天然满足每组最多选一件；A 只用倒序说明 0/1 与完全背包的差异，B 在此基础上叠加「外层枚举组、内层枚举组内物品」的三层流程，难度从入门升到普及-。"
  - oj: "roj"
    problem_id: "1294"
    reason: "B 的分组背包直接沿用 A 教的「一维 f[v] + 倒序枚举容量避免物品重复叠加」这一步，只在其外再套一层枚举组的循环"
  - oj: "luogu"
    problem_id: "U661986"
    reason: "B 直接复用 A 教的容量倒序枚举，把倒序读旧值的性质从「每件物品只选一次」推广到「每组最多选一件，同组物品不叠加」。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1272
---

[[TOC]]

## 题目描述

一个最多能装 $V$（$V \leqslant 200$）公斤的背包，$N$（$N \leqslant 30$）件物品重量 $W_i$、价值 $C_i$，划分为 $T$（$T \leqslant 10$）组，每组最多选一件。第一行输入 $V, N, T$，随后 $N$ 行每行 $W_i, C_i, P$（重量、价值、组号）；输出一行，为最大总价值。如样例输入 `10 6 3 / 2 1 1 / 3 3 1 / 4 8 2 / 6 9 2 / 2 8 3 / 3 9 3`，输出 `20`（选 $(3,3)$、$(4,8)$、$(3,9)$）。

## 思路

设 $dp[cap]$ 为容量不超过 $cap$ 的最大价值，三层循环：外层枚举组、容量倒序、内层枚举组内物品做 $dp[cap] = \max(dp[cap], dp[cap-W_j]+C_j)$。容量倒序让每个格子只读上一组的旧值，同组物品不会叠加，天然满足每组最多选一件；$dp[cap]$ 单调不减，答案即 $dp[V]$。

## 参考代码

@include-code(./main.cpp, cpp)
