---
oj: "roj"
problem_id: "3507"
title: "装箱问题"
description: '把装箱问题化成"体积=价值"的 0/1 背包：逐件物品倒序扫容量做一维 DP，dp[V] 即最大装载体积，答案为 V-dp[V]。'
difficulty: "普及-"
date: 2026-10-02 04:05
updated: 2026-10-06 12:15
toc: true
tags: ["动态规划", "背包", "01背包", "python"]
favorite: false
favorite_reason: ""
categories: ["动态规划"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3507
---

[[TOC]]

## 题目描述

容量为 V（0<V≤20000）的箱子，有 n（0<n≤30）件体积为正整数的物品，任取若干件装入箱内，使箱子剩余空间最小。
输入第一行 V，第二行 n，之后 n 行每行一件物品体积；输出一个整数，即最小剩余空间。
样例输入 `24 / 6 / 8 / 3 / 12 / 7 / 9 / 7`，输出 `0`。

## 思路

把"体积"同时当作"价值"，问题就是 0/1 背包：最大化装入的总体积，答案即 V 减去该最大值。用一维 dp[c] 表示容量 c 能装下的最大体积，每件物品倒序扫容量做 dp[c]=max(dp[c],dp[c-w]+w)，总时间 O(nV)。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
