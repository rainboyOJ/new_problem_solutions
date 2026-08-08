---
oj: "luogu"
problem_id: "P3385"
title: "【模板】负环"
description: "从节点 1 运行 SPFA，以最短路边数达到 n 判断可达负环。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["负环", "SPFA", "最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3385
---

[[TOC]]

### 题意

判断从节点 1 能到达的区域内是否存在负环。

### 思路

只把 1 入队做 SPFA。每次成功松弛时记录新路径边数 `count[v]=count[u]+1`；简单最短路至多含 `n-1` 条边，达到 `n` 说明存在可不断缩短的环。

### Python 知识

- `deque` 实现松弛队列，`bytearray` 保存入队状态。
- 正边按题意添加双向，负边只添加输入方向。
- 多组答案最后统一 `join` 输出。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

SPFA 最坏 `O(nm)`，空间 `O(n+m)`。

### 总结

题目只问从 1 可达的负环，不能把所有节点无条件作为同一可达源处理。
