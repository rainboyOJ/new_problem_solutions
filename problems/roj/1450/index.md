---
oj: "roj"
problem_id: "1450"
title: "「一本通 1.4 例 3」Knight Moves"
description: "将棋盘格子建为无权图，利用 BFS 逐层扩展求骑士从起点到终点的最少移动步数。"
difficulty: "入门"
date: 2026-09-30 11:11
updated: 2026-10-05 23:56
toc: true
tags:
  - "广度优先搜索"
  - "图论"
  - "最短路"
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1450
---

[[TOC]]

## 题目描述

计算国际象棋中骑士（马）从棋盘上一个格子跳到另一个格子所需的最少步数，每步可走 8 个「日」字方向。

**输入**：第一行是骑士数量 $n$；每个骑士占 3 行：第一行是棋盘大小 $L$（棋盘为 $L \times L$，坐标 $[0, L-1]$），后两行是起点 $(x_1, y_1)$ 和终点 $(x_2, y_2)$。

**输出**：对每个骑士输出一行最少步数；起点与终点相同则输出 0。例如输入棋盘大小 8、起点 `0 0`、终点 `7 0`，输出 `5`；起点 `1 1`、终点 `1 1` 则输出 `0`。

数据范围：$4 \le L \le 300$，保证 $0 \le x, y \le L-1$。

## 思路

把每个格子看成无权图中的节点，骑士的 8 个马步位移就是边，从起点 BFS 逐层扩展。`dist[x][y]` 记录到该格子的最少步数，每步代价为 1，所以首次扩展到终点时的距离就是答案；起点等于终点时直接输出 0。复杂度为每次询问 $O(L^2)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
