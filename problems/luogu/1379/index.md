---
oj: "luogu"
problem_id: "P1379"
title: "八数码难题"
description: "把九宫格编码为 bytes 状态，从起点 BFS 到固定目标得到最少移动次数。"
difficulty: "普及+/提高"
date: 2026-07-16 20:10
toc: true
tags: ["BFS", "状态搜索", "八数码", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1379
---

[[TOC]]

### 题意

每次把空格与上下左右棋子交换，求给定八数码到固定目标的最少步数。

### 思路

每个棋盘是图上的一个节点，每次合法交换是一条单位边，因此 BFS 第一次到达目标的距离就是最短步数。九个字符直接作为不可变 `bytes`，可放入字典判重。

预先为九个空格位置计算可交换下标。扩展时转成 `bytearray` 原地交换，再转回 `bytes` 作为新状态。

### Python 知识

- `collections.deque` 提供 $O(1)$ 队首弹出。
- `distance = {state: 0}` 同时承担判重与距离记录。
- 赋值表达式在邻居推导式中复用行列坐标。

### 代码

@include-code(./main.py, python)

### 复杂度

可达状态不超过 $9!/2$，时间和空间均为状态数的线性量级。

### 总结

状态数量可控且每步代价相同，BFS 是最稳妥的最短路算法。
