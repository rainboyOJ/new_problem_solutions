---
oj: "luogu"
problem_id: "P5960"
title: "【模板】差分约束"
description: "把 x_c-x_c'<=y 转成 c' 到 c 的边，用最短路构造可行解。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["差分约束", "SPFA", "负环", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5960
---

[[TOC]]

### 题意

为一组 `x_c-x_c'<=y` 不等式求任意可行解，或判断无解。

### 思路

不等式等价于 `x_c <= x_c' + y`，建边 `c' -> c` 权 `y`。所有距离初始为 0 相当于超级源向每点连 0 边；若出现负环则无解，否则最终距离就是一组可行解。

### Python 知识

- `deque(range(1,n+1))` 一次把所有点加入超级源队列。
- `bytearray(b"\x01")*(n+1)` 紧凑初始化入队标记。
- Python 条件表达式直接选择输出解或 `NO`。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

SPFA 最坏 `O(nm)`，空间 `O(n+m)`。

### 总结

差分约束的建边方向来自把不等式写成一次松弛公式。
