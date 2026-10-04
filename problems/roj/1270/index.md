---
oj: "roj"
problem_id: "1270"
title: "混合背包"
description: "一维 dp[j] 表示容量 j 的最大价值；完全背包正序更新，01 与多重背包倒序更新，多重背包用二进制拆分。"
difficulty: "入门"
date: 2026-09-30 02:38
updated: 2026-10-05 07:38
toc: true
tags: ["动态规划", "背包", "01背包", "完全背包", "多重背包"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1270
---

[[TOC]]

## 题目描述

背包容量 $M$（$M \le 200$），有 $N$ 件物品（$N \le 30$），第 $i$ 件重量 $W_i$、价值 $C_i$、可取件数 $P_i$：$P_i = 0$ 表示无限件，$P_i = 1$ 表示只能取一次，$P_i > 1$ 表示至多取 $P_i$ 件。求总重量不超过 $M$ 时的最大总价值。

输入第一行为 $M$、$N$，之后 $N$ 行每行三个整数 $W_i$、$C_i$、$P_i$；输出一行一个整数表示最大总价值。样例输入为 `10 3`、`2 1 0`、`3 3 1`、`4 5 4`，输出 `11`。

## 思路

用一维滚动数组 `dp[j]` 表示容量 $j$ 能获得的最大价值：完全背包（$P=0$）正序更新，允许同一物品重复选取；01 背包与多重背包倒序更新，避免重复选取。多重背包把 $P$ 二进制拆成 $1, 2, 4, \dots$ 件一组当 01 物品处理，任意取法都能凑出。时间复杂度 $O(NM + M\sum \log P_i)$，空间 $O(M)$。

## 参考代码

@include-code(./main.cpp, cpp)
