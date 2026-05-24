---
oj: "luogu"
problem_id: "P3387"
title: "【模板】缩点"
date: 2025-12-29 10:52
toc: true
tags: ["scc","dag"]
desc: "scc 然后dag"
source: https://www.luogu.com.cn/problem/P3387
pre:
 - luogu,P1314
book:
 - bookid
---

[[TOC]]


这道题是 **Tarjan 缩点 + DAG 最长路** 的经典组合拳。

## 题目解析

1. 为什么要缩点？

   题目允许“重复经过点和边”，但“权值只计算一次”。这意味着如果你进入了一个强连通分量（SCC），你可以把里面所有的点权全部拿到，然后离开。缩点后，每个 SCC 变成一个新点，新点的权值是原 SCC 内所有点权之和。

2. 缩点后的图是什么？

   缩点后的图是一个 有向无环图（DAG）。

3. 如何求最大权值和？

   在 DAG 上求“点权和最大”的路径。由于是 DAG，我们可以使用 拓扑排序 + 动态规划 (DP)。

   - 设 $dist[i]$ 为到达缩点后的新点 $i$ 的最大权值和。
   - 转移方程：$dist[v] = \max(dist[v], dist[u] + weight\_scc[v])$。

## 代码 

@include-code(./1.cpp, cpp)

