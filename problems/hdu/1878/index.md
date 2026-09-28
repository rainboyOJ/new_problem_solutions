---
oj: "HDU"
problem_id: "1878"
title: "欧拉回路"
difficulty: "普及/提高-"
date: 2026-01-05 12:30
updated: 2026-06-21 21:34
toc: true
tags: ["欧拉回路"]
desc: "欧拉回路模板题"
pre: []
common:
  - oj: "OpenJ_Bailian"
    problem_id: "1300"
    reason: "同为无向图欧拉回路/路径的度数判定题，适合对比基础条件和含指定起终点的条件。"
source: https://vjudge.net/problem/HDU-1878
---

[[TOC]]

## 题目解析

模板题

核心: 

1. 图连通
    1. 可以一条边都没有
    2. 所有的有边的点都连通
2. 没有度为奇数的点

## 代码 

@include-code(./1.cpp, cpp)

