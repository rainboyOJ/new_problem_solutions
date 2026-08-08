---
oj: "luogu"
problem_id: "P3178"
title: "[HAOI2015] 树上操作"
description: "HLD 把子树和根路径化为区间，两个 Fenwick 树支持区间加与区间和。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "树状数组", "区间加", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3178
---

[[TOC]]

### 题意

支持单点加、子树加和根到节点路径和。

### 思路

DFS 序把子树变成一个区间；HLD 把根路径拆成少量区间。Fenwick 的“区间加、区间和”模板用两棵树维护差分的一阶系数，逐段求和即可。

### Python 知识

- 两棵 Fenwick 的 `prefix_sum` 公式是 Python 中实现区间加区间和的常用模板。
- `range_add(dfn[x], dfn[x], value)` 统一了单点加和区间加接口。
- 路径循环只处理重链顶端，不需要递归查询。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次操作 `O(log^2 n)`，空间 `O(n)`。

### 总结

HLD 负责树结构，Fenwick 负责序列区间；两个模块组合后接口很清晰。
