---
oj: "roj"
problem_id: "1348"
title: "城市公交网建设问题（最小生成树）"
description: "Kruskal 最小生成树：边按造价排序 + 并查集贪心选边，最后按 (u,v) 字典序输出。"
difficulty: "普及-"
date: 2026-09-30 06:23
updated: 2026-10-05 11:15
toc: true
tags: ["最小生成树", "Kruskal", "贪心", "并查集", "图论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1348
---

[[TOC]]

## 题目描述

给定 n 个城市（1<n≤100）和 e 条无向边，每条边给出两个端点和修建造价。要求选出 n-1 条边把所有城市连通且总造价最少——即**最小生成树**，输出这 n-1 条边的两个端点（小端在前）。样例：5 个城市 8 条候选边，最小生成树为 1-2 / 2-3 / 3-4 / 3-5，总造价 19。

## 思路

Kruskal 模板：把全部边按造价从小到大排序，依次扫描，若两端未连通就用并查集把两个连通块合并；选满 n-1 条边即停。最后把选中的边按端点 (u,v) 字典序排序输出。

## 参考代码

@include-code(./main.cpp, cpp)