---
oj: "roj"
problem_id: "2051"
title: "香甜的黄油"
description: "枚举每个牧场作为放糖点，从该点跑一次堆优化 Dijkstra，利用无向图最短路的对称性直接得到所有牛的路程和，取最小值。"
difficulty: "普及"
date: 2026-10-01 05:06
updated: 2026-10-07 12:15
toc: true
tags: ["图论", "最短路", "dijkstra", "枚举"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1381"
    reason: "B 每枚举一个候选放糖点就跑一次与 A 完全同款的堆优化 Dijkstra（含 `if d > dist[u]: continue` 跳过过期堆记录这一步），A 只求 1 到 n 单条最短路，B 在此之上叠加无向图对称换向、按牛数加权求和与枚举全部牧场取 min。"
  - oj: "luogu"
    problem_id: "P1747"
    reason: "A 教的『无向图最短路可反向』被 B 用作关键的换向：把每头牛到放糖点 x 反转成从 x 单源 Dijkstra 一次，从而把 N 次单终点计算压成 P 次单源计算。"
  - oj: "roj"
    problem_id: "2037"
    reason: "B 复用 A 教的「无向图最短路对称换向」这一步：把每头牛到糖点反转成从糖点出发，从而每个候选点只需一次单源 Dijkstra，再改为加权求和取最小"
common: []
recommend: []
source: https://roj.ac.cn/problem/2051
---

[[TOC]]

## 题目描述

给定 $P$ 个牧场、$C$ 条无向正权道路，以及 $N$ 头牛各自所在的牧场。选一个牧场放糖，使所有牛到该牧场的最短路之和最小，输出这个最小值。$P \le 800$，$C \le 1450$。

## 思路

无向图最短路对称，从放糖点跑单源 Dijkstra 即可得到所有牛到它的距离。枚举每个牧场作为放糖点，取所有牛路程和的最小值。同一牧场多头牛用计数加权。

## 参考代码

@include-code(./main.cpp, cpp)
