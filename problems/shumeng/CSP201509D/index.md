---
oj: "shumeng"
problem_id: "CSP201509D"
title: "高速公路"
description: "用 Tarjan 分解强连通分量，分量内任意两城都构成便利城市对。"
difficulty: "普及+/提高-"
date: 2026-07-31 16:21
toc: true
tags: ["强连通分量", "Tarjan", "有向图"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201509D
---

[[TOC]]

## 形式化题目

给定一个 $n$ 个点 $m$ 条单向边的有向图。若城市 A 能到达城市 B，且 B 也能到达 A，则 $(A, B)$ 是一个便利城市对（$(A, B)$ 与 $(B, A)$ 视为同一对）。求便利城市对的数量。

## 思路

先看一个小数据基准：对每个城市做一次 BFS，直接检查所有城市对是否互相可达。

@include-code(./brute.cpp, cpp)

`brute.cpp` 用一个 `reach[i][j]` 表格记录可达关系，再两两判断，时间复杂度为 $O(n(n+m))$，只适合小数据，但逻辑完全照题意，适合对拍。

### 关键观察

互相可达的两个城市恰好位于同一个**强连通分量**：分量内任意两点两两互通，分量之间则单向可达、无法互相到达。

### Tarjan 求强连通分量

用 Tarjan 算法找出所有强连通分量。每找到一个大小为 $s$ 的分量，它内部贡献的便利城市对数为：

$$\binom{s}{2} = \frac{s(s-1)}{2}$$

累加所有分量的贡献即为答案。注意 $n$ 最大 $10000$，$s$ 最大可接近 $n$，$s(s-1)/2$ 要用 `long long` 存储。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：Tarjan 每个点和边各访问常数次，$O(n+m)$。
- 空间：邻接表与 Tarjan 栈，$O(n+m)$。

## 总结

“双向可达”直接对应强连通分量，这是有向图问题最常见的转化。求出分量大小后，城市对数量由组合数一次性算出，不需要逐一枚举点对。