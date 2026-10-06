---
oj: "roj"
problem_id: "2040"
title: "usaco-3.1.1 最短网络"
description: "基于稠密完全图邻接矩阵的 Prim 算法求最小生成树"
difficulty: "普及-"
date: 2026-10-01 04:29
updated: 2026-10-06 10:10
toc: true
tags:
  - "图论"
  - "最小生成树"
favorite: false
favorite_reason: ""
categories:
  - "图论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2040
---

[[TOC]]

## 题目描述

约翰有 $n$ 个农场，要铺设最短光纤把它们都连通。输入给出 $n$ 及一个 $n \times n$ 的邻接矩阵，矩阵元素表示两农场之间的距离（对称，对角线为 0）。求连接所有农场的最小光纤总长度。

## 思路

这是一道稠密图最小生成树模板题。$n \leqslant 100$，直接在邻接矩阵上跑 $O(n^2)$ 的 Prim 算法即可：每次把到当前树距离最小的农场加入树，再用它到其余农场的距离更新最小距离数组，最后累加答案。

## 参考代码

@include-code(./main.cpp, cpp)
