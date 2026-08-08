---
oj: "luogu"
problem_id: "P3313"
title: "[SDOI2014] 旅行"
description: "HLD 拆路径，按宗教维护动态线段树，回答同宗教城市的评级和与最大值。"
difficulty: "省选/提高"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "动态线段树", "路径查询", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3313
---

[[TOC]]

### 题意

支持修改城市宗教、修改评级，以及查询路径上指定宗教城市的评级和或最大值。

### 思路

HLD 把路径拆成 DFS 序区间。为每种宗教维护一棵动态线段树，只有该宗教当前出现的位置建立节点；宗教修改就是旧树叶子清零、新树叶子写入，评级修改只更新当前宗教的一片叶子。路径上逐段查询并合并和与最大值。

### Python 知识

- `array("i")`/`array("q")` 作为动态线段树节点池，避免为每个节点创建对象。
- `roots[color]` 保存每种宗教的根，空节点 0 共享给所有宗教。
- 点更新沿 DFS 序路径迭代回溯，区间查询返回 `(sum, max)` 元组。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次路径查询 `O(log^2 n)`，单点变更 `O(log n)`；动态节点数为所有实际宗教-位置组合的对数级总量。

### 总结

当筛选条件是动态颜色时，可以把颜色放到外层根数组，把位置线段树节点按需创建。
