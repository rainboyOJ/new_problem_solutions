---
oj: "roj"
problem_id: "1381"
title: "城市路（Dijkstra）"
description: "无向带重边图上跑堆优化 Dijkstra，边权非负时第一次弹出 n 即最短路，不可达输出 -1。"
difficulty: "普及-"
date: 2026-07-05 21:47
updated: 2026-10-05 12:30
toc: true
tags: ["最短路", "Dijkstra", "堆", "图论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1381
---

[[TOC]]

## 题目描述

给定 $n$ 个城市、$m$ 条双向道路，求从城市 $1$ 到城市 $n$ 的最短距离；若不可达输出 `-1`。

输入：$n\ m$，随后 $m$ 行每行 `a b c` 表示城市 $a$、$b$ 间有一条长度为 $c$ 的路。

数据范围：$1 \le n \le 2000$，$1 \le m \le 10000$，$0 \le c \le 10000$。

样例输入：

```
5 5
1 2 20
2 3 30
3 4 20
4 5 20
1 5 100
```

样例输出：

```
90
```

## 思路

边权非负，用堆优化 Dijkstra：用邻接表存无向图，小根堆按当前距离取点，第一次弹出城市 $n$ 时即为最短路；不可达输出 `-1`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
