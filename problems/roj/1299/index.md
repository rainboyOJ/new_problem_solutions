---
oj: "roj"
problem_id: "1299"
title: "糖果"
description: "把「所选糖果总数模 K 的余数」作为背包状态，每个余数只保留最大总和：dp[j] = max(dp[j], old[(j - a%K)%K] + a)，答案取 dp[0]。"
difficulty: "普及-"
date: 2026-09-30 03:53
updated: 2026-10-07 12:15
toc: true
tags: ["动态规划", "背包", "同余", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "U661986"
    reason: "B 把 A 教的「同一状态只保留最优值、每件物品只选一次」照搬到一维 0/1 背包上：dp[j] 同样只留最优总和并用旧表做一次取/不取转移（代码 old[from]+value 更新 dp[j]），只是把状态从容量换成总和模 K 的余数，并叠加环形回绕 (j - r + k) % k。"
  - oj: "roj"
    problem_id: "1294"
    reason: "A 教的「一维 dp 表上逐件物品做每件只用一次的 0/1 转移」正是 B 的每一轮循环：B 只把状态维从容量换成模 K 的余数，并用旧表快照代替倒序枚举来维持 0/1 语义，再叠加同余数取最大总和与答案取 dp[0] 的建模。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1299
---

[[TOC]]

## 题目描述

有 $N$ 件产品，第 $i$ 件含 $a_i$ 颗糖果；从中选若干件（可空），使所选总数是 $K$ 的倍数，求能达到的最大总数，凑不出则输出 $0$。

**输入**：第一行 $N\ K$，接下来 $N$ 行每行一个 $a_i$。**输出**：最大可行总数。数据范围 $N \leqslant 100$，$K \leqslant 100$，$a_i \leqslant 10^6$。

样例输入 `5 7` / `1 2 3 4 5`，输出 `14`：选 $2+3+4+5=14$，是 $7$ 的倍数且最大。

## 思路

判断合法性只看总和模 $K$ 的余数，而同一余数下总和越大越好，所以每个余数只保留最大总和。`dp[j]` 表示总数模 $K$ 余 $j$ 时的最大值，逐件糖果用上一轮的旧表做 0/1 转移 `dp[j] = max(dp[j], old[(j - a % K + K) % K] + a)`，答案即 `dp[0]`，复杂度 $O(NK)$。

## 参考代码

@include-code(./main.cpp, cpp)
