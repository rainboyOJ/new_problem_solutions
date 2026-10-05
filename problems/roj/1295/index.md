---
oj: "roj"
problem_id: "1295"
title: "装箱问题"
description: "体积既当重量又当收益的 0/1 背包：dp[s] 表示体积 s 能否被拼出，从大到小刷一遍，最后从 V 往下找最大可达体积，V 减去它即最小剩余空间。"
difficulty: "普及-"
date: 2026-09-30 03:39
updated: 2026-10-05 08:17
toc: true
tags: ["动态规划", "01背包", "背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1295
---

[[TOC]]

## 题目描述

箱子容量 $V$（$0 \leqslant V \leqslant 20000$），有 $n$（$0 < n \leqslant 30$）个物品，第 $i$ 个体积 $w_i \leqslant 10000$，每件至多选一次，求装完后最小的剩余空间。
输入第一行 $V$、第二行 $n$，随后 $n$ 行每行一个体积；输出一个整数表示最小剩余空间。样例输入 `24 6 8 3 12 7 9 7`，输出 `0`。

## 思路

物品体积既是重量也是收益，这就是 0/1 背包。用 `dp[s]` 表示体积 $s$ 能否被拼出，处理体积 $w$ 时从大到小刷 `dp[s] |= dp[s-w]`，保证每件只用一次。
最后从 $V$ 往下找第一个可达的 $s$，即最多能装下的体积，答案是 $V-s$。

## 参考代码

@include-code(./main.cpp, cpp)
