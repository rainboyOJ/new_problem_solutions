---
oj: "roj"
problem_id: "1266"
title: "【例9.10】机器分配"
description: "分组背包 DP：f(i,j)=max_k f(i-1,j-k)+a[i][k] 求前 i 家恰好分 j 台的最大盈利，并用 res 记录决策 O(N) 回溯输出分配方案。"
difficulty: "普及"
date: 2026-09-30 02:26
updated: 2026-10-05 07:37
toc: true
tags: ["动态规划", "背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1266
---

[[TOC]]

## 题目描述

总公司有 $M$ 台设备分给 $N$ 家分公司（$N,M\leqslant 100$）。第 $i$ 家分 $j$ 台获利 $a_{i,j}$，每家可分 $0\sim M$ 台，但总台数不超过 $M$，求最大盈利及一组分配方案。输入第一行 $N\ M$，随后 $N$ 行每行 $M$ 个整数即盈利表；输出第一行最大盈利，随后 $N$ 行每行「公司编号 分到台数」。样例输入 `3 3` / `30 40 50` / `20 30 50` / `20 25 30`，输出 `70` 与 `1 1`、`2 1`、`3 1`。

## 思路

设 $f_{i,j}$ 为前 $i$ 家公司恰好分掉 $j$ 台的最大盈利，第 $i$ 家分 $k$ 台则有 $f_{i,j}=\max_{0\leqslant k\leqslant j}(f_{i-1,j-k}+a_{i,k})$，即分组背包，复杂度 $O(NM^2)$。要输出方案，就在转移处用 $res_{i,j}$ 记下取到最大的 $k$，最后从 $f_{N,M}$ 起倒推每家分到的台数。

## 参考代码

@include-code(./main.cpp, cpp)
