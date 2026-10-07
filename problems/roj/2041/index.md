---
oj: "roj"
problem_id: "2041"
title: "usaco-3.1.2 总分"
description: "完全背包：dp[t] 表示限时 t 的最大得分，容量正序使种类可重复选取。"
difficulty: "普及-"
date: 2026-10-01 04:43
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "背包", "完全背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1294"
    reason: "A 教的一维背包 f[v] 状态与转移被 B 完整沿用，B 只把 A 的倒序改成容量维正序，从而由 0-1 选取变为可重复选取的完全背包。"
  - oj: "luogu"
    problem_id: "U661986"
    reason: "B 的完全背包完全沿用 A 教的一维转移式 dp[t]=max(dp[t],dp[t-t_i]+p_i) 与「扫描方向决定件数」这一步，只是把 A 的容量倒序（每件只选一次）换成正序（种类可重复选），并在此之上叠加按耗时升序处理与被支配种类剪枝。"
  - oj: "luogu"
    problem_id: "U661988"
    reason: "A 教的容量正序枚举=物品可重复选，正是 B 完全背包解法中 range(minutes, limit+1) 这一步的直接复用，B 只是在其上叠加被支配种类剪枝"
common: []
recommend: []
source: https://roj.ac.cn/problem/2041
---

[[TOC]]

## 题目描述

给定竞赛限时 $M$ 与 $N$ 个题目种类，第 $i$ 个种类每道题耗时 $t_i$、得分 $p_i$，可以选任意多道。求总耗时不超过 $M$ 时的最大得分。

输入格式：第一行 $M,N$；接下来 $N$ 行每行两个整数，先得分后耗时。输出一行最大得分。

样例：$M=300,N=4$，种类为 $(100,60),(250,120),(120,100),(35,20)$，输出 $605$。

## 思路

令 $dp[t]$ 表示限时 $t$ 内的最大得分。外层枚举种类，内层容量从小到大扫描（正序），则 $dp[t-t_i]$ 已含本轮结果，同一种类可被反复选取，即完全背包。按耗时升序处理，若 $dp[t_i] \ge p_i$ 则该种类被支配，跳过。

## 参考代码

@include-code(./main.cpp, cpp)
