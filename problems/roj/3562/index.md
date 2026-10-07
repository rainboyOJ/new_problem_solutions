---
oj: "roj"
problem_id: "3562"
title: "传球游戏"
description: "环上传球计数：设 f(i,j) 为传 i 次后球在 j 手中的方案数，每步只能从左右邻居转移，答案 f(m,0)，O(mn) 递推。"
difficulty: "普及"
date: 2026-10-02 07:48
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "计数", "环"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "leetcodecn"
    problem_id: "climbing-stairs"
    reason: "A 教的“某格方法数等于其前驱邻格方法数之和对并定初值”被 B 直接用作传球 DP：把 i-1、i-2 换成环上 (j-1)%n、(j+1)%n 即可"
  - oj: "luogu"
    problem_id: "P1255"
    reason: "B 直接复用 A 教的「最后一步只有两种来源就相加」计数模板：把 dp[i]=dp[i-1]+dp[i-2] 换成环上左右邻居两个前驱相加，仅额外套一层 (j±1)%n 绕回，难度落在 A 之上两档。"
  - oj: "leetcodecn"
    problem_id: "pascals-triangle"
    reason: "B 的 DP 逐层计数直接沿用了 A 教的「本层每格 = 上一层两个相邻格子相加」这一步二维逐层递推，只把上一层下标加取模改成左右邻居并补了边界与环的处理"
common: []
recommend: []
source: https://roj.ac.cn/problem/3562
---

[[TOC]]

## 题目描述

$n$ 个同学围成一圈，编号 $0 \sim n-1$（小蛮为 $0$ 号）。球最初在 $0$ 号手中，每次必须传给左右相邻同学之一。求恰好传 $m$ 次后球回到 $0$ 号手中的方案数。

输入格式：一行两个整数 $n, m$（$3 \le n \le 30, 1 \le m \le 30$）。

输出格式：一个整数，表示方案数。

样例输入：`3 3`，样例输出：`2`。

## 思路

设 $f(i, j)$ 为传 $i$ 次后球在 $j$ 号手中的方案数，则 $f(i, j) = f(i-1, (j-1) \bmod n) + f(i-1, (j+1) \bmod n)$，边界 $f(0, 0) = 1$，答案 $f(m, 0)$。直接按次数逐层递推即可。

## 参考代码

@include-code(./main.cpp, cpp)
