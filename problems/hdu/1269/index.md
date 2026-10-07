---
oj: "HDU"
problem_id: "1269"
title: "迷宫城堡"
difficulty: "普及/提高-"
date: 2025-12-29 10:31
updated: 2026-10-07 10:45
toc: true
tags: ["scc","模板题目"]
desc: "求scc数量,scc模板题目"
pre: []
common:
  - oj: "luogu"
    problem_id: "P2863"
    reason: "同为 Tarjan 求 SCC 的基础模板题，都是直接验证强连通分量性质。"
source: https://vjudge.net/problem/HDU-1269
book:
 - scc
---

[[TOC]]

## 题目解析

模板题目, 求scc的数量

这是一个非常经典的强连通分量（SCC）练习题。


1. **核心要求**：题目要求判断图中“任意两个房间是否相互连通”。
2. **数学定义**：在有向图中，如果图中任意两个点 $u$ 和 $v$ 都可以互相到达，那么这个图被称为**强连通图 (Strongly Connected Graph)**。
3. **判定方法**：
   - 利用 Tarjan 算法求出图中所有的强连通分量（SCC）。
   - 如果整个图**只有一个**强连通分量（即 `scc_cnt == 1`），且这个分量包含了所有的 $N$ 个顶点，那么这个图就是强连通的。
   - 否则，输出 "No"。

## 代码 

@include-code(./1.cpp, cpp)

