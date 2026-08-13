---
oj: "luogu"
problem_id: "P5836"
title: "[USACO19DEC] Milk Visits S"
description: "根路径 G 前缀和配合倍增 LCA 容斥，O(log n) 回答路径上是否出现指定品种。"
difficulty: "普及"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "倍增", "前缀和", "树", "USACO"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5836
---

[[TOC]]

## 形式化题目

给定一棵 $N$ 个节点的树，每个节点有颜色 `G` 或 `H`。有 $M$ 次询问，每次给定两个端点 $a$、$b$ 和一种颜色 $C$，问树上的唯一简单路径 $a \to b$（含端点）上是否存在颜色为 $C$ 的节点。依次输出每个询问的答案：存在输出 `1`，否则输出 `0`。

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 对每次询问从 $a$ 出发沿树 DFS 找通向 $b$ 的唯一路径，再逐点统计 G 的个数：单次询问 $O(N)$，总复杂度 $O(NM)$，在 $10^5$ 的数据上不可行。

关键观察：**只数一种颜色，剩下的用路径长度补**。以 1 为根，预处理每个节点到根路径上 G 的数量 `sumG[i]`，那么任意路径 $a \to b$ 上 G 的数量可以容斥得到：

$$\mathrm{cntG} = \mathrm{sumG}(a) + \mathrm{sumG}(b) - 2 \cdot \mathrm{sumG}(\mathrm{lca}(a,b)) + [\mathrm{color}(\mathrm{lca}) = G]$$

路径上的点数 $\mathrm{len} = \mathrm{depth}(a) + \mathrm{depth}(b) - 2 \cdot \mathrm{depth}(\mathrm{lca}) + 1$，于是 $\mathrm{cntH} = \mathrm{len} - \mathrm{cntG}$。回答询问时，看目标品种的计数是否大于 0 即可。

这句话的几何含义：路径 $a \to b$ 等于"根到 $a$ 的路径"和"根到 $b$ 的路径"的并集去掉公共前缀"根到 LCA"，再把被减了两次的 LCA 补回来。用样例树（颜色串 `HHGHG`，边 1-2、2-3、2-4、1-5）验证一条询问：

```text
       1 (H)
      / \
    2 (H) 5 (G)
   / \
 3 (G) 4 (H)

询问 1 -> 4，喜欢 H：路径是 1 2 4，三个节点全是 H
sumG(1) = 0    sumG(4) = 0    lca(1,4) = 1
cntG = sumG(1) + sumG(4) - 2*sumG(1) + [color(1)=G] = 0
len = depth(1) + depth(4) - 2*depth(1) + 1 = 1 + 3 - 2 + 1 = 3
cntH = len - cntG = 3 > 0   ->  输出 1（样例第一位的 `1`）
```

再看两个退化情况验证公式的鲁棒性：询问 `1 3 G` 时 LCA 仍是 1，`cntG = sumG(3) = 1 > 0`，输出 `1`；询问 `5 5 H` 时路径只有节点 5 自己（它是 G），`cntH = 1 - 1 = 0`，输出 `0`，正好对应样例输出 `10110` 的最后一位。可见当 LCA 恰是某个端点、甚至 $a = b$ 时，公式无需特判。

实现上，一次 BFS 就能同时求出 `depth`、`sumG` 和倍增祖先表 `up[u][j]`；每次询问先用倍增表 $O(\log N)$ 求 LCA，再 $O(1)$ 套公式。这个预处理结构直接来自 rbook 的《[倍增求 LCA](https://rbook2.roj.ac.cn/tree-algo/jump-lca/index.html)》（模板 `lca-binary-lifting`）。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：预处理 $O(N \log N)$，每次询问 $O(\log N)$，总 $O((N + M) \log N)$。
- 空间：倍增表 $O(N \log N)$，`depth`、`sumG` 与邻接表 $O(N)$。

## 总结

这道题是"树上路径点权计数"最标准的入门题：只维护一种颜色的根前缀，配合 LCA 容斥，把路径计数压到 $O(\log N)$。要点有两个——一是"只数 G，H 用路径长度补"，二是"路径 = 两条根路径 - 公共前缀 + LCA"。这两个技巧可以直接迁移到路径点权和、路径异或和等树上问题；以后学树上差分时，公式形式完全一样，只是把计数换成了差分值。

## 图示解析

这张 ASCII 图展示整道题的解题路线：

```text
朴素模拟（brute.cpp）
  每次询问沿路径 DFS 找路，逐点统计颜色      O(N) 每次询问
        |
        | 瓶颈：不复用信息，m 次询问 O(N*M) 太大
        v
关键观察（容斥）
  路径 a->b = 根到 a 的路径 + 根到 b 的路径
              - 公共前缀（根到 LCA）+ LCA 自己
  只数 G 一种颜色，H 用路径长度补
        |
        v
倍增 LCA + 根前缀计数（main.cpp）
  一次 BFS 预处理 depth / sumG / up 倍增表
  询问：O(log N) 求 LCA，O(1) 套容斥公式
  cntG > 0 或 cntH > 0 决定答案 1/0
        |
        v
复杂度 O((N + M) log N)，空间 O(N log N)
```

图中三条主线分别对应"暴力慢在哪里""观察到什么性质""正式解如何利用这个性质"。容斥公式把"统计任意路径上的颜色"变成"查两个根前缀和、减去一次公共前缀"，难度从逐点遍历降到两次表格查询；倍增 LCA 只负责回答公式里的 $\mathrm{lca}(a,b)$ 一项，两者拼装就是全部实现。
