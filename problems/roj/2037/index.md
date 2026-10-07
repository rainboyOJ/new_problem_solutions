---
oj: "roj"
problem_id: "2037"
title: "usaco-2.4.3 回家"
description: "52 个牧场的无向带权图，把源点从每只母牛换成谷仓，一次 Dijkstra 得到 A..Y 到 Z 的最短距离，取最小者。"
difficulty: "普及-"
date: 2026-10-01 04:29
updated: 2026-10-06 09:59
toc: true
tags: ["图论", "最短路", "Dijkstra", "堆", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2037
---

[[TOC]]

## 题目描述

52 个牧场标记为 `a`..`z`、`A`..`Z`，其中 `A`..`Y` 各有一只母牛，`Z` 是谷仓。给定 `P` 条无向正权边（允许重边、自环），所有母牛沿最短路走向谷仓，求最先到达的母牛标记及路径长度。保证最优解唯一。

## 思路

无向图满足 $\operatorname{dist}(v,Z)=\operatorname{dist}(Z,v)$，因此只需从谷仓 `Z` 跑一次 Dijkstra，再在 `A`..`Y` 中取距离最小者即可。重边保留最短一条，正权自环不影响最短路。

## 参考代码

@include-code(./main.cpp, cpp)
