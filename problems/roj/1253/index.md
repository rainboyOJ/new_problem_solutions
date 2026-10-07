---
oj: "roj"
problem_id: "1253"
title: "抓住那头牛"
description: "把坐标看成顶点、三种操作看成边权为 1 的边，BFS 逐层扩展，首次到达 K 的层号即最少分钟数；起点大于等于终点时答案直接是 N-K。"
difficulty: "普及-"
date: 2026-09-30 02:13
updated: 2026-10-07 12:15
toc: true
tags: ["搜索", "BFS", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1255"
    reason: "B 的 main.cpp 直接复用 A 教的「无权图 BFS 按层扩展、首次入队即最短步数、dist=-1 兼作访问标记」这一步，只把网格四方向换成 -1/+1/*2 三种操作，并叠加 [0,2K] 搜索上界与 K<=N 时答案 N-K 的收口"
common: []
recommend: []
source: https://roj.ac.cn/problem/1253
---

[[TOC]]

## 题目描述

农夫在数轴上的点 $N$，牛停在点 $K$（$0 \leqslant N, K \leqslant 100000$）。农夫每分钟可以从 $x$ 走到 $x-1$、$x+1$ 或 $2x$（位置不能为负），求走到 $K$ 的最少分钟数。

输入一行两个整数 $N$ 和 $K$，输出一个整数表示最小分钟数。

**样例输入**：`5 17`　**样例输出**：`4`（走法 `5 -> 4 -> 8 -> 16 -> 17`）。

## 思路

把每个坐标看成一个状态、三种操作看成边权为 1 的边，答案是 $N$ 到 $K$ 的最短路。边权全相等，用 BFS 从 $N$ 逐层扩展，首次访问 $K$ 时的层号就是最少分钟数。搜索范围限制在 $[0, 2K]$：越过 $2K$ 后回到 $K$ 至少要 $>K$ 步，不如从 $N$ 一路 `+1` 的 $K-N$ 步，所以更远的点不可能是最优。若 $K \leqslant N$，只有 `-1` 能下降，答案直接是 $N-K$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
