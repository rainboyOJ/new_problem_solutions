---
oj: "luogu"
problem_id: "B3611"
title: "【模板】传递闭包"
description: "用 Python 整数位集加速 Warshall 传递闭包。"
difficulty: "普及"
date: 2026-07-17 03:00
toc: true
tags: ["传递闭包", "Floyd", "位运算", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B3611
---

[[TOC]]

### 题意

由有向图邻接矩阵求任意两点是否可达。

### 思路

每一行可达集合编码成整数位集。若 `i` 能到 `k`，就把 `k` 的整行可达集合并入 `i`；这正是 Warshall 转移，但一次 OR 同时处理全部终点。

### Python 知识

- Python 大整数天然是可变长位集。
- `mask |= value << index` 编码一行邻接矩阵。
- 右移与按位与逐位恢复输出。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

进行 `O(n^2)` 次大整数 OR，空间 `O(n^2)` 位。

### 总结

布尔矩阵行可以压成整数，把最内层循环交给底层位运算。
