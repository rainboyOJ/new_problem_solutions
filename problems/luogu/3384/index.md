---
oj: "luogu"
problem_id: "P3384"
title: "【模板】重链剖分 / 树链剖分"
description: "用 HLD 把树上路径和子树映射为 DFS 序区间，再由懒标记线段树维护区间加和。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "线段树", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3384
---

[[TOC]]

### 题意

支持树上路径加、路径和、子树加和子树和，结果对 `P` 取模。

### 思路

重链剖分把任意路径拆成 `O(log n)` 个连续 DFS 序区间；子树天然是 `[dfn[x], dfn[x]+size[x)-1]`。线段树保存区间和并懒加，逐段处理路径即可。

### Python 知识

- 用栈保存 `(node, chain_top)`，沿重儿子迭代，避免递归分解。
- `list(map(int, input().split()))` 统一读取四种操作长度。
- 模运算集中放在 `apply` 和合并处，保持节点值有界。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n)`，每次操作 `O(log^2 n)`，空间 `O(n)`。

### 总结

HLD 的接口就是“路径拆段 + 区间数据结构”；先掌握拆段循环，再替换线段树统计量。
