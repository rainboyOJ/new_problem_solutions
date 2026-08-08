---
oj: "luogu"
problem_id: "P3398"
title: "仓鼠找 sugar"
description: "用 LCA 枚举路径交点候选，并用 DFS 序祖先关系判断两条路径是否相交。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "路径相交", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3398
---

[[TOC]]

### 题意

判断树上路径 `a-b` 与 `c-d` 是否有公共节点。

### 思路

两条路径的交点若存在，必出现在六个端点两两 LCA 以及两条路径各自 LCA 中。用 DFS 序区间判断祖先关系，节点 `x` 在路径 `a-b` 上当且仅当它是 `lca(a,b)` 的后代且为 `a` 或 `b` 的祖先；枚举候选即可。

### Python 知识

- DFS 序和子树大小把祖先判断变成两个整数区间比较。
- 候选集合用元组保存，最多六个节点，不需要构造路径列表。
- 倍增 LCA 函数可以复用在多个候选上。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次询问进行常数次 `O(log n)` LCA，空间 `O(n log n)`。

### 总结

树上路径相交不必真的走路径，找到有限个结构性候选点即可。
