---
oj: "roj"
problem_id: "2033"
title: "usaco-2.3.4 货币系统"
description: "完全背包计数：外层按面值分组、金额正序执行 ways[j] += ways[j-c]，统计凑出金额 N 的组合数。"
difficulty: "普及-"
date: 2026-10-01 04:15
updated: 2026-10-07 12:15
toc: true
tags: ["动态规划", "完全背包", "组合计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "U661988"
    reason: "B 把 A 教的「一维数组容量/金额正序枚举，让 dp[c-v] 已含本物品贡献」这一完全背包关键步骤，直接用到计数版上（main.py 的 for amount in range(coin, n+1): ways[amount] += ways[amount-coin]），只在 A 的空间压缩基础上叠加二维递推降维与组合计数（外层按面值分组）的额外流程。"
  - oj: "roj"
    problem_id: "1294"
    reason: "B 的组合计数沿用 A 教的一维滚动数组状态设计与「枚举方向决定物品能否重复取用」这一步：A 用倒序枚举容量保证每件至多选一次，B 把同一 ways 数组改为按面值外层、金额内层正序枚举（main.py 的 ways[amount] += ways[amount - coin]），使 ways[j-c] 含本轮值从而面值可重复取用，B 原文也直接以 0/1 背包倒序扫描作对照；在此之上 B 才叠加按面值分组去重、max 换成方案数累加与 ways[0]=1 边界。"
  - oj: "luogu"
    problem_id: "U661986"
    reason: "B 的完全背包计数沿用 A 教的一维滚动数组状态设计并把扫描方向规则翻转使用：A 用倒序让 dp[c-v] 保持上轮值以保证每件物品只选一次，B 在 main.py 里用正序让 ways[j-c] 含本轮值，从而同一面值可重复取用，B 原文也直接以倒序 0/1 背包作对照说明这一分界；在此之上 B 才叠加按面值分组去重、max 换成方案数累加与 ways[0]=1 边界。"
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
