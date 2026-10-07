---
oj: "roj"
problem_id: "1348"
title: "城市公交网建设问题（最小生成树）"
description: "Kruskal 最小生成树：边按造价排序 + 并查集贪心选边，最后按 (u,v) 字典序输出。"
difficulty: "普及-"
date: 2026-09-30 06:23
updated: 2026-10-07 13:50
toc: true
tags: ["最小生成树", "Kruskal", "贪心", "并查集", "图论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1536"
    reason: "B 的 Kruskal 主循环在 B 的代码里逐行指认了 A 教的这一步：find(u)、find(v) 后「两端代表元不同才合并」（father[ru]=rv，main.py 第 61-63 行），A 只教了并查集判连通与合并这一层，B 在它外面叠加按权排序、贪心选满 n-1 条边和复现 std 快排。"
  - oj: "luogu"
    problem_id: "P1551"
    reason: "B 的 Kruskal 把 A 教的「find 取代表元并比较是否同块」直接用作选边判据：代码里 `ru, rv = find(father,u), find(father,v)` 后 `if ru != rv: father[ru] = rv` 才选边，只是在此外层叠加按权排序、割性质贪心与复现 std 不稳定快排的输出处理。"
  - oj: "luogu"
    problem_id: "P3367"
    reason: "B 的 Kruskal 直接用 A 教的 find 找代表元判同集合这一步来决定每条边是否选中（代码 ru!=rv 才 father[ru]=rv），并沿用 A 的路径压缩，只是在外层叠加按权排序、割性质贪心与复现 std 不稳定快排的输出要求。"
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

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)