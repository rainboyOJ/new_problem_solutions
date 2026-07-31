---
oj: "shumeng"
problem_id: "CSP201512E"
title: "矩阵"
description: "在 GF(2) 中提取 Krylov 状态序列的最小递推，用多项式快速幂求 A^k b。"
difficulty: "省选/NOI-"
date: 2026-07-31 16:21
toc: true
tags: ["线性代数", "GF(2)", "矩阵快速幂"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512E
---

[[TOC]]

### 题意

对 GF(2) 可逆矩阵的初始向量，回答多组 $A^k b$。

### 思路

向量序列 $b,Ab,A^2b,\ldots$ 最多在 $m$ 维空间中线性无关。位集高斯消元找到首个线性关系 $A^db=\sum c_iA^ib$，于是任意高次幂都可对这个递推多项式取模。对每个 $k$ 用 GF(2) 多项式快速幂得到 $x^k\bmod P(x)$，再线性组合前 $d$ 个状态。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

位集预处理约为 $O(m^3/64)$；每次询问为多项式的位集快速幂。

### 总结

不需要显式平方 $m\times m$ 矩阵。只针对给定初始向量建立 Krylov 序列，维数最多为 $m$。
