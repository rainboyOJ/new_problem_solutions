---
oj: "luogu"
problem_id: "P3379"
title: "【模板】最近公共祖先（LCA）"
description: "用非递归建树和倍增祖先表回答大规模最近公共祖先询问。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "倍增", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3379
---

[[TOC]]

### 题意

给定根树，回答任意两点的最近公共祖先。

### 思路

先求深度和父亲。`up[j][u]` 表示 `u` 的 `2^j` 级祖先。查询时先把较深节点提升到同层，再从最高层向下尝试同时跳跃。

### Python 知识

- `array("i")` 保存每层祖先表，避免 `n log n` 个 Python 整数对象。
- 前向星 `head/to/next_edge` 让 50 万节点的邻接结构保持紧凑。
- 分块写出答案，避免一次性保存几十万字符串。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n log n)`，每次查询 `O(log n)`，空间 `O(n log n)`。

### 总结

LCA 倍增的两个动作是“提升深度”和“从高位向下试跳”。
