---
oj: "luogu"
problem_id: "P3128"
title: "[USACO15DEC] Max Flow P"
description: "对每条运输路径做树上点差分，最后自底向上汇总并取最大经过次数。"
difficulty: "普及+/提高"
date: 2026-01-03 21:13
toc: true
tags: ["树上差分", "LCA", "倍增", "树"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3128
---

[[TOC]]

### 题意

给定一棵树和 `k` 条运输路径。每条路径的所有点，包括两个端点，都会被经过一次。

要求输出被经过次数最多的点的经过次数。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力逐条路径枚举点会超时。这里是树上路径点加一的离线问题，使用树上点差分。

对路径 $u \to v$，设：

```text
g = lca(u, v)
```

差分标记为：

```text
diff[u]++
diff[v]++
diff[g]--
diff[parent[g]]--
```

最后自底向上汇总子树差分。这样路径上的点都会加一，路径外的点不会被影响。

为什么要在 `g` 和 `parent[g]` 减一？

- 从 `u` 和 `v` 向根累加时，`g` 会收到两边贡献；
- `diff[g]--` 让 `g` 只保留一次；
- `diff[parent[g]]--` 把 `g` 以上祖先的多余贡献抵消。

所有路径做完差分后，统一汇总并取最大值即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

LCA 预处理 $O(n log n)$，每条路径处理 $O(log n)$。

总时间复杂度为 $O((n+k) \log n)$，空间复杂度为 $O(n log n)$。

### 总结

多次树上路径点加一，优先考虑树上点差分。

点差分的核心是四个标记位置：两个端点、LCA、LCA 的父亲。
