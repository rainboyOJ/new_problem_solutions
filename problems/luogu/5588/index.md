---
oj: "luogu"
problem_id: "P5588"
title: "小猪佩奇爬树"
description: "把同色节点的路径约束化为 Steiner 子树直径，并用两侧组件计数路径数量。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["树的直径", "LCA", "树上计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5588
---

[[TOC]]

### 题意

对每种颜色，统计路径恰好经过该颜色全部节点的点对数量。

### 思路

若同色节点不共线，则没有路径能全部经过，答案为 0。否则同色节点都在它们直径端点 `x,y` 的路径上，路径经过全部节点等价于经过 `x-y`。切断 `x`、`y` 方向的第一条边，两个外侧组件大小相乘就是答案；没有该颜色时所有点对都合法。

### Python 知识

- 颜色节点用“同色链表”存储，避免为百万种颜色创建百万个 Python 列表。
- `array` 保存边、父亲、祖先和答案，控制百万节点内存。
- 分块输出一百万行结果，避免构造巨大字符串列表。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

总节点参与两次同色最远点扫描，时间约 `O(n log n)`，空间 `O(n log n)`。

### 总结

“经过一组点”先看这些点是否共线；共线后只需关注两个端点和两侧组件。
