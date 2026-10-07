---
oj: "roj"
problem_id: "2033"
title: "usaco-2.3.4 货币系统"
description: "完全背包计数：外层按面值分组、金额正序执行 ways[j] += ways[j-c]，统计凑出金额 N 的组合数。"
difficulty: "普及-"
date: 2026-10-01 04:15
updated: 2026-10-06 09:59
toc: true
tags: ["动态规划", "完全背包", "组合计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2033
---

[[TOC]]
## 题目描述
给定 $V$ 种货币面值（$1 \leqslant V \leqslant 25$）和目标金额 $N$（$1 \leqslant N \leqslant 10{,}000$），求用这些面值恰好凑出 $N$ 的方案数，按**组合**计数：`8x2+2x1` 与 `2x1+8x2` 算同一种，答案保证在 `long long` 范围内。输入第 1 行是两个整数 $V$ 和 $N$，接下来 $V$ 行每行一个面值；输出单独一行方案数。
```text
3 10
1 2 5
```
样例输出为 `10`。
## 思路
完全背包计数：设 `ways[j]` 为凑出金额 $j$ 的方案数，`ways[0] = 1`，外层枚举每种面值 $c$、内层金额 $j$ 正序执行 `ways[j] += ways[j-c]`。外层按面值分组保证同一方案的货币顺序不重复计数（组合而非排列），正序使 `ways[j-c]` 已含本轮值、同一面值可重复选。
## 参考代码
@include-code(./main.cpp, cpp)
