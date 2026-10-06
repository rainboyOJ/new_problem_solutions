---
oj: "roj"
problem_id: "2041"
title: "usaco-3.1.2 总分"
description: "完全背包：dp[t] 表示限时 t 的最大得分，容量正序使种类可重复选取。"
difficulty: "普及-"
date: 2026-10-01 04:43
updated: 2026-10-06 10:10
toc: true
tags: ["动态规划", "背包", "完全背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
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
