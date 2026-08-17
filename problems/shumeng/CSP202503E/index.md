---
oj: "shumeng"
problem_id: "CSP202503E"
title: "收费标准评估"
description: "用 Link-Cut Tree 的路径矩阵维护动态树形 DP，同时维护虚子树贡献以支持换根和子树查询。"
difficulty: "提高+/省选-"
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
---

[[TOC]]

## 形式化题目

一棵树，每个节点有权值 $a_i$（可为负）。以某点为根时，定义"基本费用"为**所有包含根节点的连通子图**中权值和的最大值。维护四种操作：查询某子树内的最优连通子图、修改点权、换根、断边重连，并在每次操作后输出当前基本费用。

## 思路

核心是动态树上的树形 DP。先看每次重建树的朴素做法：

@include-code(./brute.cpp, cpp)

### 树形 DP 的两个量

对每个节点 $u$ 定义：

- $F_u$：必须包含 $u$ 的连通子图的最大权和；
- $G_u$：$u$ 所在子树内任意连通子图的最大权和。

有转移：

$$
F_u = a_u + \sum_{v \in child(u)} \max(0, F_v), \qquad
G_u = \max(F_u, \max_{v \in child(u)} G_v)
$$

由于允许选择负权节点（即使收益为负也要选，因为必须连通），$\max(0, F_v)$ 表示"接不接这个孩子的子树"。

### 把转移写成矩阵

在一条首选路径（实链）上，下方子链的状态 $(F,G)$ 经过当前节点 $u$ 后的变换为：

$$
F'=\max(a_u + F, a_u), \qquad
G'=\max(a_u + F, G, a_u, b_u)
$$

其中 $a_u$ 是节点权值加上虚子树 $\max(0,F)$ 之和，$b_u$ 是虚子树 $G$ 的最大值。这是一个 max-plus 矩阵变换，可以用 $3\times 3$ 矩阵表示，Link-Cut Tree 的 Splay 节点维护路径上矩阵的复合。

### 虚子树用 multiset 维护

`access` 操作会让实链和虚子树互相转换。对每个节点用两个 multiset 分别保存虚子树的 $\max(0,F)$ 总和与 $G$ 最大值，从而支持 $O(\log n)$ 的插入删除。于是：

- 基本费用 = 根节点的 $F$ 值；
- 换根后 `access(u)`，$u$ 的虚子树贡献直接给出其子树内 $G$；
- 改权、断边、连边都是 Link-Cut Tree 的标准操作。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

每次操作均摊 $O(\log n)$ 次 Splay 旋转，加上虚子树 multiset 的 $O(\log n)$，总均摊复杂度 $O(\log^2 n)$；空间复杂度 $O(n)$。

## 总结

把树形 DP 看作"一个节点对其路径孩子状态的函数"，就可以用 max-plus 矩阵在动态树路径上复合。Link-Cut Tree 天然只维护实链，虚子树部分用可删除的有序集合补全，就同时支持换根、点权和动态加删边。