---
oj: "roj"
problem_id: "3636"
title: "[noip2016-普及] 海港"
description: "24 小时滑动窗口统计不同国籍数：船整进整出队列，国籍计数 +1/-1，减到 0 删键，答案 O(1)。"
difficulty: "普及-"
date: 2026-10-02 12:07
updated: 2026-10-06 15:55
toc: true
tags: ["滑动窗口", "队列", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3636
---

[[TOC]]

## 题目描述

小 K 在海港按时间记录了 $n$ 艘到达的船：第 $i$ 艘船在时刻 $t_i$（秒）到达，载 $k_i$ 名乘客，国籍依次为 $x_{i,1},\dots,x_{i,k_i}$。对每个 $i$，统计满足 $t_i - 86400 < t_j \le t_i$（最近 24 小时）的所有船 $j$（$1 \le j \le i$）上的乘客共来自多少个**不同国籍**，输出 $n$ 行。

输入：第一行一个正整数 $n$；接下来 $n$ 行，每行前两个整数 $t_i, k_i$，后跟 $k_i$ 个整数表示乘客国籍。输出：$n$ 行，第 $i$ 行为第 $i$ 艘船到达后的统计结果。

数据范围：$1 \le n \le 10^5$，$\sum k_i \le 3\times 10^5$，$1 \le x_{i,j} \le 10^5$，$1 \le t_i \le 10^9$（$t_i$ 递增）。

样例 1：输入 `3`、`1 4 4 1 2 2`、`2 2 2 3`、`10 1 3`，输出依次为 `3`、`4`、`4`。

## 思路

$t_i$ 递增，窗口两端只会单调右移，按船为单位维护队列：船 $i$ 先整船进窗（每个国籍计数 +1），再把队首满足 $t_j \le t_i - 86400$ 的旧船整船出窗（计数 -1，注意窗口左端是开区间，取等即出）。用数组 `cnt[国籍]` 维护窗口内人数，减到 0 时不同国籍数 `distinct` 减一，每轮直接输出 `distinct`；每个乘客只进、出各一次，总复杂度 $O(n + \sum k_i)$。

## 参考代码

@include-code(./main.cpp, cpp)
