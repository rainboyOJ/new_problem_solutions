---
oj: "roj"
problem_id: "1376"
title: "信使"
description: "消息并行传播等价于单源最短路：哨所 v 收到命令的时刻就是 1 到 v 的最短路长，边权为正跑 Dijkstra，答案是所有 dist 的最大值，不连通输出 -1。"
difficulty: "普及-"
date: 2026-09-30 07:42
updated: 2026-10-05 12:23
toc: true
tags: ["最短路", "Dijkstra", "图论"]
favorite: false
favorite_reason: ""
categories: ["图论"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1376
---

[[TOC]]

## 题目描述

前线有 $n$ 个哨所（$1 \le n \le 100$）和 $m$ 条通信线路，每条线路连接两个哨所，送信需要 $k$ 天。指挥部设在哨所 $1$，命令沿线路并行传播。第一行输入 $n,m$，随后 $m$ 行每行三个整数 $i,j,k$。输出所有哨所都收到命令的最短天数；若有哨所收不到，输出 `-1`。

样例输入为 `4 4` / `1 2 4` / `2 3 7` / `2 4 1` / `3 4 6`，输出 `11`。

## 思路

每个哨所信使充足，收到信后能同时向所有邻居转发，所以哨所 $v$ 收到命令的时刻就是哨所 $1$ 到 $v$ 的最短路长度，答案取所有最短路的最大值。边权为正，用 Dijkstra 求单源最短路，若某个哨所仍不可达则输出 `-1`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
