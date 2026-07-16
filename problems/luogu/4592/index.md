---
oj: "luogu"
problem_id: "P4592"
title: "[TJOI2018] 异或"
description: "Euler 前缀版本回答子树，根到点版本配合 LCA 四根差分回答路径最大异或。"
difficulty: "省选/NOI-"
date: 2026-07-16 19:57
toc: true
tags: ["可持久化Trie", "Euler序", "LCA", "树上路径", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4592
---

[[TOC]]

### 题意

树上点有权值，询问某个子树或两点路径中，点权与给定 `z` 的最大异或值。

### 思路

DFS 序中一个子树是连续区间 `[entry[x], exit[x]]`。按 Euler 顺序建立 Trie 前缀版本，就能用两个版本的计数差回答子树。

路径查询另为每个节点建立“根到该点所有点权”的版本 `path_root[u]`。设 `a=lca(x,y)`，路径点权多重集等于：

```text
root[x] + root[y] - root[a] - root[parent[a]]
```

每个二进制位同时查看四个版本的目标儿子；正版本计数之和大于负版本时即可走入。LCA 用普通倍增求出。

两类版本的节点结构完全相同，因此共用三个节点数组。

### Python 知识

- 显式进入/离开事件栈同时得到 `entry`、`exit` 和 DFS 顺序，避免递归爆栈。
- `map(previous.__getitem__, previous)` 构造 LCA 倍增下一层。
- `array("i")` 保存父亲、深度、版本根和 Trie 节点，控制六百万级节点的内存。
- 查询先读成整数列表，再按操作类型解包不同参数。

### 代码

@include-code(./main.py, python)

### 复杂度

预处理 $O(n\log n+30n)$，每次子树询问 $O(30)$，路径询问 $O(\log n+30)$；空间 $O(n\log n+30n)$。

### 总结

子树靠 Euler 区间差，路径靠根版本四项容斥；两种树上集合查询最终都落到同一个“版本节点计数差”。
