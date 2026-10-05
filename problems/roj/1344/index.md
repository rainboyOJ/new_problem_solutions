---
oj: "roj"
problem_id: "1344"
title: "【例4-4】最小花费"
description: "把手续费 z% 的边换算成放大因子 100/(100-z)，A 到 B 的最小放大倍数路径就是放大 Dijkstra 的求和最优，答案再乘 100 并保留 8 位小数。"
difficulty: "普及-"
date: 2026-09-30 06:08
updated: 2026-10-05 10:46
toc: true
tags: ["图论", "最短路", "Dijkstra", "堆", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1344
---

[[TOC]]

## 题目描述

给定 $n$ 个人的转账网络（$1\le n\le 2000$），$m$ 条无向边 $(x,y,z)$ 表示 $x$ 与 $y$ 互相转账要扣 $z%$ 手续费（$z<100$）。钱沿一条路径每过一条 $(u,v,z)$ 就被扣掉 $z%$，给定起点 $A$ 和终点 $B$（保证可达），求 $A$ 至少转出多少钱，才能让 $B$ 到账恰好 100 元。答案保留 8 位小数。

输入：第一行 $n,m$；接着 $m$ 行 `x y z`；最后一行 `A B`。

输出：`A` 最少需要的总费用，精确到小数点后 8 位。

样例：

```
3 3
1 2 1
2 3 2
1 3 3
1 3
```

输出：`103.07153164`。

## 思路

把手续费 $z%$ 的边换算成"放大因子" $w=100/(100-z)>1$，$A$ 最少转出金额 $=100\times$ 路径上 $w$ 的连乘；连乘最小等价于对数域非负权和最小，直接在倍数上跑二叉堆 Dijkstra，`dist[A]=1`，答案 `dist[B]*100` 即输出。

## 参考代码

@include-code(./main.cpp, cpp)