---
oj: "roj"
problem_id: "1262"
title: "挖地雷"
description: "边都从小编号指向大编号的 DAG 上求点权和最大的路径：倒序 DP，dp[u] = a[u] + max(dp[v])，用 nxt 数组还原路径。"
difficulty: "普及-"
date: 2026-09-30 02:13
updated: 2026-10-05 07:27
toc: true
tags:
  - "线性DP"
  - "DAG"
  - "图论"
  - "DP"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1262
---

[[TOC]]

## 题目描述

地图上有 $n$（$n \le 200$）个地窖，每个地窖中埋有一定数量的地雷，并给出若干条单向连接路径，路径保证从小编号地窖指向大编号地窖，且不会出现绕回出发点的路线。某人可以从任一地窖开始挖地雷，然后沿连接路径往下挖（每到一个地窖只能选择一条路径继续），直到无路可走为止。要求设计一个挖地雷的方案，使挖到的地雷最多。

输入格式：第一行为地窖个数 $n$；第二行依次为每个地窖中地雷的个数；下面若干行每行为 $x_i\ y_i$，表示从 $x_i$ 可到 $y_i$（$x_i < y_i$），最后一行为 `0 0` 表示结束。

输出格式：第一行输出挖地雷的顺序 $k_1-k_2-\dots-k_v$；第二行输出挖到的最多的雷数。

输入样例：

```text
6
5 10 20 5 4 5
1 2
1 4
2 4
3 4
4 5
4 6
5 6
0 0
```

输出样例：

```text
3-4-5-6
34
```

## 思路

所有边都从小编号指向大编号，图是一个 DAG，且 $1 \sim n$ 本身就是拓扑序。设 $dp[u]$ 表示从 $u$ 出发能挖到的最多地雷数，从 $n$ 倒推到 $1$，有 $dp[u] = a_u + \max_{u \to v} dp[v]$（无出边时 $dp[u]=a_u$），并用 $nxt[u]$ 记录最优后继；答案取 $dp[1..n]$ 的最大值，从对应起点沿 $nxt$ 走即可还原路径。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
