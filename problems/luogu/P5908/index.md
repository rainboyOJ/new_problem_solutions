---
oj: "luogu"
problem_id: "P5908"
title: "猫猫和企鹅"
description: "从 1 号点 BFS，统计距离不超过 d 的非根节点。"
difficulty: "普及"
date: 2026-07-17 02:00
toc: true
tags: ["树", "BFS", "队列", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5908
---

[[TOC]]

### 题意

树根为 1，统计距离根不超过 `d` 的企鹅数量，根节点本身没有企鹅。

### 思路

树边权全为 1，所以从 1 做 BFS 即可得到最短距离。弹出距离为 `d` 的节点后不再扩展，访问到的新节点就是一只可拜访的企鹅。

### Python 知识

- `collections.deque` 的 `popleft` 是真正的 `O(1)` 队列操作。
- 邻接表用列表的列表表达无向树，遍历代码直观。
- 距离数组用 `-1` 同时表示“未访问”。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

单位边树上的“距离不超过阈值”就是一次限深 BFS。
