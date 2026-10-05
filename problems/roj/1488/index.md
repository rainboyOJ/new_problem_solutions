---
oj: "roj"
problem_id: "1488"
title: "「一本通 3.1 练习 1」新的开始"
description: "引入超级源点，把「建电站费用」和「拉电网费用」统一成边权，在 n+1 个点的完全图上求最小生成树即得最小总花费。"
difficulty: "普及-"
date: 2026-09-30 14:15
updated: 2026-10-06 00:23
toc: true
tags: ["图论", "最小生成树", "Prim", "超级源点", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1488
---

[[TOC]]

## 题目描述

有 $n$ 口矿井，编号 $1 \sim n$。两种通电方式：

- 在第 $i$ 口矿井建发电站，费用 $v_i$，一座电站可供给任意多口矿井；
- 在第 $i$、$j$ 口矿井之间拉电网，费用 $p_{i,j}$（$p_{i,j}=p_{j,i}$，$p_{i,i}=0$）。

要求每口矿井都有电，求最小总花费。$1 \leqslant n \leqslant 300$，$0 \leqslant v_i, p_{i,j} \leqslant 10^5$。

**输入**：第一行 $n$；接下来 $n$ 行每行一个 $v_i$；然后 $n$ 行每行 $n$ 个整数构成矩阵 $p$。  
**输出**：一个整数，最小总花费。

样例输入/输出见 problem.md。

## 思路

引入超级源点 $S$，给每个矿井 $i$ 连一条 $(S,i)$ 边、权为 $v_i$。于是建电站和拉电网都变成边，问题转化为在 $n+1$ 个点的完全图上求最小生成树。$n=300$ 为稠密图，用朴素 Prim $O(n^2)$ 即可。

## 参考代码

@include-code(./main.cpp, cpp)
