---
oj: "luogu"
problem_id: "P2052"
title: "[NOI2011] 道路修建"
description: "一次根树遍历求每条边两侧规模，按长度乘规模差累加费用。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["树形 DP", "子树大小", "前向星", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2052
---

[[TOC]]

### 题意

树边费用为边长乘以两侧国家数量之差的绝对值，求总费用。

### 思路

任选 1 为根。若父子边下方子树大小为 `size`，两侧规模分别是 `size` 与 `n-size`，边贡献就是 `weight * abs(n-2*size)`。后序累加子树大小即可。

### Python 知识

- 百万节点使用 `array` 前向星保存边，避免百万个 Python 小列表。
- `reversed(order[1:])` 只做一次自底向上汇总。
- `abs` 直接表达两侧规模差的绝对值。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

树边分割问题通常只需要知道一侧子树大小，另一侧就是 `n-size`。
