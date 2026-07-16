---
oj: "luogu"
problem_id: "P3372"
title: "【模板】线段树 1"
description: "用带懒标记的线段树维护区间和，支持区间加和区间查询。"
difficulty: "普及/提高-"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "区间加", "区间求和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3372
---

[[TOC]]

### 题意

维护数列，支持区间加法和区间求和。

### 思路

节点保存覆盖区间的和。整段加 `value` 时，区间和增加 `length * value`，并把 `value` 记在懒标记中；只有在需要访问孩子时才下传。区间查询和修改都只访问对数个节点。

### Python 知识

- `sys.stdin.buffer.readline` 减少大量操作的输入开销。
- 用几个同长度列表保存线段树字段，比为每个节点创建对象更省内存。
- `if query_left <= middle` 和 `if middle < query_right` 只递归到真正相交的子树。

### 代码

@include-code(./main.py, python)

原有 C++ 模板仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`，每次操作 `O(log n)`，空间 `O(n)`。

### 总结

懒标记就是“先在大区间记账，访问子区间时再摊开”。
