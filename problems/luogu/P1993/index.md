---
oj: "luogu"
problem_id: "P1993"
title: "小 K 的农场"
description: "把三类作物数量关系统一成差分约束边，并检测负环。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["差分约束", "负环", "SPFA", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1993
---

[[TOC]]

### 题意

判断至少、至多、相等三类农场数量关系能否同时满足。

### 思路

全部改写为 `x_v <= x_u+w`：至少关系反向并取负权，至多关系按上界建边，相等建两条 0 边。所有点从 0 开始做最短路，出现负环即矛盾。

### Python 知识

- 不同长度操作行用 `list(map(...))` 统一解析。
- `deque` 和 `bytearray` 是 SPFA 的常用组合。
- 输出只取决于是否检测到负环。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

SPFA 最坏 `O(nm)`，空间 `O(n+m)`。

### 总结

文字中的至少/至多先移项，统一为一个松弛方向后更不容易建反边。
