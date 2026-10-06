---
oj: "roj"
problem_id: "3141"
title: "数字组合"
description: "01 背包计数：f[j] 表示和恰好为 j 的选数方案数，倒序转移统计方案。"
difficulty: "普及"
date: 2026-10-01 20:08
updated: 2026-10-06 11:58
toc: true
tags: ["动态规划", "01背包问题"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3141
---

[[TOC]]

## 题目描述

给定 $N$ 个正整数 $A_1, A_2, \ldots, A_N$，从中选出若干个数（每个数至多选一次），使它们的和恰好为 $M$，求有多少种选择方案。数值相同但位置不同的数算不同的选择。

输入格式：第一行两个整数 $N$ 和 $M$；第二行 $N$ 个整数表示 $A_1, A_2, \ldots, A_N$。输出格式：一个整数，表示方案数。数据范围：$1 \le N \le 100$，$1 \le M \le 10000$，$1 \le A_i \le 1000$。

样例：三种方案是 1+1+2 的两种下标组合与 2+2。输入样例：

```text
4 4
1 1 2 2
```

输出样例：`3`

## 思路

01 背包计数：设 $f[j]$ 为选出的数之和恰好为 $j$ 的方案数，初始 $f[0]=1$，每读入一个数 $x$ 就做转移 $f[j] \mathrel{+}= f[j-x]$，表示"不选 $x$/选 $x$"两类方案合并。$j$ 必须从 $M$ 倒序枚举到 $x$，保证 $f[j-x]$ 还是本轮的旧值，每个数至多被选一次；答案即 $f[M]$。

## 参考代码

@include-code(./main.cpp, cpp)
