---
oj: "luogu"
problem_id: "P3976"
title: "[TJOI2015] 旅游"
description: "HLD 加区间加线段树维护有向路径上的最大买卖差值。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "线段树", "最大子段差", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3976
---

[[TOC]]

### 题意

沿 `a -> b` 的路径选择先买后卖的两个城市，输出最大利润，然后让路径上所有价格增加 `v`。

### 思路

线段树节点维护最小值、最大值、正向最大差和反向最大差。正向合并的跨段候选是 `right.max-left.min`，反向则是 `left.max-right.min`。HLD 拆段时，`a` 侧区间反向、`b` 侧区间正向，按旅行顺序合并；查询后再做路径区间加。

### Python 知识

- 元组 `(min, max, forward, backward)` 让方向信息随区间一起返回。
- `reverse_info` 只交换两个方向的差值，最值不变。
- `None` 作为空合并结果，避免构造无效哨兵。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次查询和更新 `O(log^2 n)`，空间 `O(n)`。

### 总结

路径有方向时，区间统计量必须同时保存正向和反向两套信息。
