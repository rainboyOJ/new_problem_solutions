---
oj: "luogu"
problem_id: "P4114"
title: "Qtree1"
description: "树链剖分 + 线段树，边权映射到较深端点的点权，路径最大边权转化为路径上非 LCA 节点的入边权最大值。"
difficulty: "提高+/省选-"
date: 2026-10-29 16:32
updated: 2026-10-29 16:38
toc: true
tags: ["树链剖分", "线段树", "边权", "路径最大值", "树"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4114
---

[[TOC]]

### 题意

给定一棵带边权的树，支持两种操作：

- `CHANGE i t`：把第 i 条边的边权改为 t
- `QUERY a b`：查询 a 到 b 路径上的最大边权；若 a==b，输出 0

### 思路

树上边权路径查询的经典做法是树链剖分 + 线段树。

核心观察：**把每条边权映射到较深的端点（子节点）的“入边”点权上**。这样：

- 路径 u-v 上的边 = 从 u 跳到 LCA 再跳到 v 过程中，所有非 LCA 节点的入边
- 当 u==v 时，路径上没有边，最大值为 0

重链剖分后：

- `fa / dep / sz / son / top / dfn` 描述树
- `a[u]` 存放 u 的入边权值（根为 0）
- 线段树维护 `base[dfn[u]] = a[u]`，支持单点修改 + 区间最大值

跳链时：

- 不同链：取整条重链 `[dfn[top[u]], dfn[u]]` 的最大值
- 同一链：u 是 v 的祖先时，取 `[dfn[u]+1, dfn[v]]`，跳过 LCA 本身

`CHANGE` 单点修改：找到该边对应的较深端点，用 `dfn` 更新线段树。

实现参考 rbook 模板 hld 的全局数组写法，sgt 段只做区间最大值，hld 段负责边权映射与路径拆分。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 预处理：O(n)
- 每次操作：O(log^{2} n)
- 空间：O(n)

### 总结

边权转点权是处理树上边权查询的常用技巧。关键是：

1. 正确选择“存放边权的节点”（较深端点）
2. 查询时跳过 LCA（`dfn[u]+1`）
3. a==b 时直接输出 0
