---
oj: "shumeng"
problem_id: "CSP201412D"
title: "最优灌溉"
description: "按水渠费用升序用 Kruskal 选择不成环的边，得到连接全部麦田的最小生成树。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["最小生成树", "并查集", "贪心"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201412D
---

[[TOC]]

### 题意

把麦田看作顶点、水渠看作带权边，要求用最小费用让所有麦田连通。

### 思路

先看小数据枚举边集的暴力：

@include-code(./brute.cpp, cpp)

这正是最小生成树问题。将所有水渠按费用从小到大排序，依次考虑每条边：如果连接了两个不同连通块，就选择它；如果两端已经连通，选择会形成环，跳过。并查集维护当前连通块。

选出 $n-1$ 条边后，得到的费用就是答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序占 $O(m\log m)$，每条边进行并查集操作，时间复杂度为 $O(m\log m)$；空间复杂度为 $O(n+m)$。

### 总结

Kruskal 的贪心依据是：当前最便宜的能连接两个连通块的边可以安全加入某棵最小生成树。并查集负责快速判断是否成环。
