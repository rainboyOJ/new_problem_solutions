---
oj: "luogu"
problem_id: "P3379"
title: "【模板】最近公共祖先（LCA）"
description: "用倍增表预处理每个点的 2^j 级祖先，将每次 LCA 查询降到 O(log n)。"
difficulty: "普及/提高-"
date: 2026-01-03 20:47
toc: true
tags: ["LCA", "倍增", "树"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3379
---

[[TOC]]

### 题意

给定一棵以 `root` 为根的树，多次询问两个点的最近公共祖先。

最近公共祖先指同时是两个点祖先且深度最大的点。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素做法是逐层爬父亲。若树是一条链，单次询问可能爬很多层，因此需要倍增优化。

预处理：

```text
up[x][j] = x 向上跳 2^j 步到达的祖先
```

转移为：

```text
up[x][j] = up[ up[x][j-1] ][j-1]
```

查询 `x, y`：

1. 若两点深度不同，先把更深的点向上跳到同一深度；
2. 如果此时两个点相同，它就是答案；
3. 否则从大到小枚举 `j`，若 `up[x][j] != up[y][j]`，就让两个点一起向上跳；
4. 最后两个点的父亲就是 LCA。

本题数据较大，代码使用 BFS 预处理深度和父亲，避免递归 DFS 爆栈。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理 $O(n log n)$，每次查询 $O(log n)$。

空间复杂度为 $O(n log n)$。

### 总结

倍增 LCA 的核心是把“向上爬很多层”拆成二进制跳跃。

先补齐深度，再同步向上跳到 LCA 下一层，是模板中最重要的两个步骤。
