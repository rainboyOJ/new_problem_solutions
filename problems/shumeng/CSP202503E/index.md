---
oj: "shumeng"
problem_id: "CSP202503E"
title: "收费标准评估"
description: "用 Link-Cut Tree 的路径矩阵维护动态树形 DP，同时维护虚子树贡献以支持换根和子树查询。"
date: 2026-07-31 16:21
toc: true
tags: ["Link-Cut Tree", "动态树", "树形 DP"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503E
difficulty: "提高+/省选-"
---

[[TOC]]

### 题意

树上每个点有一个可能为负的权值。根固定时，基本费用是所有包含根的连通子树的最大权值和；询问 `1 u` 则改为只看当前根下 `u` 的子树，并允许游客从任意点进入。还要支持点权修改、换根和断边重连。

### 思路

小数据可以每次按当前根重建树，使用树形 DP：

@include-code(./brute.cpp, cpp)

对一个节点 `u`，设虚子树（不在当前 Link-Cut Tree 的首选路径上）的贡献为：

$$
F_u=a_u+\sum\max(0,F_v),
$$

其中 `F_u` 表示必须包含 `u` 的最大和；再令 `G_u` 表示 `u` 子树内任意连通子树的最大和，则

$$G_u=\max(F_u,\max G_v).$$

在一条首选路径上，当前节点对下方状态 `(F,G)` 的变换为：

$$F'=\max(A+F,A),\qquad G'=\max(A+F,G,A,B),$$

其中 `A=a_u+虚子树 F 贡献`，`B=虚子树 G` 的最大值。这是固定的 max-plus 矩阵变换，Link-Cut Tree 的 Splay 区间维护这些矩阵的复合。

每次 `access` 时，首选子树和虚子树互相转换，用两个有序 multiset 维护虚子树的 `max(0,F)` 总和和 `G` 最大值。于是：

- 根的基本费用是根节点的 `F`；
- `makeroot(root); access(u)` 后，`u` 的虚子树贡献直接给出其子树内的 `G`；
- 改权、换根、断边和连边均由 Link-Cut Tree 的标准操作完成。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每次操作的均摊复杂度为 `O(log n log n)`，其中第二个对数来自虚子树 multiset；空间复杂度为 `O(n)`。

### 总结

把树形 DP 看成“一个节点对其路径孩子状态的函数”，就可以用矩阵在动态树路径上复合；虚子树则用可删除的有序集合保存，补足 Link-Cut Tree 的非路径信息。
