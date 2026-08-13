---
oj: "luogu"
problem_id: "P3398"
title: "仓鼠找 sugar"
description: "两条树上路径相交当且仅当某条路径的 LCA 落在另一条路径上，用距离等式 dist(u,x)+dist(x,v)=dist(u,v) 判断点在路径上。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "倍增", "树", "路径相交"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3398
---

[[TOC]]

## 形式化题目

给定一棵 $n$ 个节点的树，给出 $q$ 次询问，每次询问给出四个节点 $a, b, c, d$。判断树上路径 $a \to b$ 与路径 $c \to d$ 是否至少共享一个节点，输出 `Y` 或 `N`。

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 每次询问先把路径 $a \to b$ 的所有点打上标记，再爬路径 $c \to d$ 检查碰撞，单次询问 $O(n)$，总复杂度 $O(nq)$，无法通过 $10^5$ 的数据。

关键观察有两个：

1. **路径的最高点是 LCA**：路径 $a \to b$ 上距根最近的点是 $p = \text{lca}(a,b)$，整条路径等于"从 $a$、$b$ 分别爬到 $p$"的两条链的并。
2. **相交判定只看两个 LCA**：两条路径相交当且仅当 $\text{lca}(a,b)$ 在路径 $c \to d$ 上，或 $\text{lca}(c,d)$ 在路径 $a \to b$ 上。如果交点存在，它必在某条路径的爬升段上，另一条路径的 LCA 必然落在这一段的祖先链里，从而在另一条路径上；反过来若某个 LCA 在对方路径上，它自己也必在己方路径上，交集显然非空。

于是问题退化成"判断一个点是否在某条路径上"。这可以用距离拆分等式：

$$\text{dist}(u, x) + \text{dist}(x, v) = \text{dist}(u, v)$$

恰好成立时 $x$ 在路径 $u \to v$ 上（树上路径唯一，$x$ 在岔路上时等式左边严格更大）。每次询问只需 $O(\log n)$ 次 LCA 调用，这就是"距离拆分"（rbook 文章《[倍增求 LCA](https://rbook2.roj.ac.cn/tree-algo/jump-lca/index.html)》中的路径包含模式）。

以样例的树为例（节点 1 为根，3 是 1 的儿子，4 的儿子是 2，2 的儿子是 5），对比两个典型询问：

```text
        1
       / \
      3   4
          |
          2
          |
          5
```

| 询问 | 路径 $a \to b$ | 路径 $c \to d$ | 输出 | 判定过程 |
| --- | --- | --- | --- | --- |
| `2 2 1 4` | $\{2\}$ | $\{1,4\}$ | N | $\text{lca}(2,2)=2$ 不在路径 $1 \to 4$ 上，$\text{lca}(1,4)=1$ 不在路径 $2 \to 2$ 上 |
| `4 1 3 4` | $\{4,1\}$ | $\{3,1,4\}$ | Y | $\text{lca}(4,1)=1$ 在路径 $3 \to 4$ 上，距离拆分 $0+1=1$ 成立 |

观察第二行：两个 LCA 都是 1，而第一行两个 LCA（2 和 1）互不在对方路径上，正好对应"共点"与"分离"两种结局。整个判定不需要构造路径点集，只比较常数个 LCA。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：预处理 $O(n \log n)$；每次询问至多 8 次 LCA 调用，$O(\log n)$，总 $O((n+q) \log n)$。
- 空间：倍增表 $O(n \log n)$，邻接表与深度数组 $O(n)$。

## 总结

树上路径相交问题的通用套路是"用 LCA 定位路径、用距离拆分判断点在路径上"：先算出两条路径各自的最高点，再检查对方的最高点是否落在自己的路径上。它把"枚举路径点"降成"常数次 LCA 查询"。rbook 的《[倍增求 LCA](https://rbook2.roj.ac.cn/tree-algo/jump-lca/index.html)》讲解了本解使用的 `BinaryLCA` 模板（`lca-binary-lifting`）：`depth`、`up`、`lca`、`dist` 四个部分直接对应代码结构。

## 图示解析

这张 ASCII 图展示整道题的解题路线：

```text
朴素模拟（brute.cpp）
  标记路径 a->b 的点，再爬路径 c->d 检查碰撞      O(n) 每次询问
        |
        | 瓶颈：枚举路径上的每个点，q 次询问 O(n*q) 太大
        v
关键观察
  路径最高点 = lca(a,b)、lca(c,d)
  两路径相交 <=> 某条路径的 LCA 落在另一条路径上
  点在路径上 <=> dist(u,x) + dist(x,v) == dist(u,v)（距离拆分）
        |
        v
倍增 LCA（main.cpp，模板 lca-binary-lifting）
  dfs 预处理 depth[] 与 up[u][j] = 2^j 级祖先      O(n log n)
  询问：p = lca(a,b)，r = lca(c,d)
  on_path(p, c, d) || on_path(r, a, b)             O(log n) 每次询问
        |
        v
复杂度 O((n + q) log n)，空间 O(n log n)
```

图中三条主线对应"暴力慢在哪""相交判定如何只依赖两个 LCA""距离拆分如何把点在路径上的判断变成常数次 LCA"。核心是把路径这个"点集合"压缩成两个结构性点（LCA），用距离等式验证归属，路径枚举的困难就此消失。
