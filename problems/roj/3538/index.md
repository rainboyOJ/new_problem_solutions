---
oj: "roj"
problem_id: "3538"
title: "[NOIP2005-普及] 采药"
description: "01 背包入门题：dp[t] 表示 t 时间内能采到的最大总价值，每株草药倒序枚举容量完成 01 转移，O(MT) 时间、O(T) 空间。"
difficulty: "普及-"
date: 2026-10-02 06:04
updated: 2026-10-06 13:35
toc: true
tags: ["动态规划", "背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3538
---

[[TOC]]

## 题目描述

山洞里有 $M$ 株草药，采第 $i$ 株需要耗时 $c_i$、价值为 $v_i$。给定总时间 $T$，要在总耗时不超过 $T$ 的前提下采一些草药，使采到的总价值最大。

**输入格式**：第一行两个整数 $T(1 \le T \le 1000)$ 和 $M(1 \le M \le 100)$；接下来 $M$ 行每行两个 $1 \sim 100$ 之间的整数，表示采摘一株草药的时间和它的价值。**输出格式**：一个整数，表示在规定时间内可以采到的草药的最大总价值。样例：输入 `70 3`、`71 100`、`69 1`、`1 2`，输出 `3`。

## 思路

这是 01 背包的定义级题目：耗时是"体积"，$T$ 是背包容量。设 $dp[t]$ 表示总耗时不超过 $t$ 时能采到的最大总价值，每株草药倒序枚举容量 $t$ 做转移 $dp[t] = \max(dp[t],\, dp[t-c_i] + v_i)$；倒序保证 $dp[t-c_i]$ 还是尚未考虑这株草药时的旧值，从而每株最多采一次。时间复杂度 $O(MT)$，空间 $O(T)$。

## 参考代码

@include-code(./main.cpp, cpp)
