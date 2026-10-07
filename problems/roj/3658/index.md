---
oj: "roj"
problem_id: "3658"
title: "铺设道路"
description: "把每天的区间填平操作看成给相邻深度差分，答案为相邻深度差的正部之和 max(d_i - d_{i-1}, 0)。"
difficulty: "普及"
date: 2026-10-02 13:43
updated: 2026-10-06 16:14
toc: true
tags:
  - 贪心
  - 差分
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3658
---

[[TOC]]

## 题目描述

道路长度为 $n$，第 $i$ 段下陷深度为 $d_i$。每次操作选一段区间 $[L,R]$（操作前区间内深度均大于 $0$），把 $d_L,\dots,d_R$ 同时减 $1$，求把整条路填平所需的最少操作次数。输入：第一行 $n$，第二行 $d_1,\dots,d_n$；输出：最少操作次数。样例输入：`n=6`，`d=[4,3,2,5,3,5]`；样例输出：`9`。数据范围：$1 \le n \le 10^5$，$0 \le d_i \le 10^4$。

## 思路

把每次操作看成砖块图（位置为列、高度为 $d_i$）里的一条横条：只有比左邻高出来的层，左邻没有砖可铺，必须以该位置为左端点新开一次操作，因此答案是相邻深度差的正部之和 $\sum_{i=1}^{n} \max(d_i - d_{i-1}, 0)$（约定 $d_0 = 0$）。一次线性扫描即可，样例即 $4+3+2=9$。

## 参考代码

@include-code(./main.cpp, cpp)
