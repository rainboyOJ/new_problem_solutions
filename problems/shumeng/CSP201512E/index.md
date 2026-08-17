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

## 形式化题目

在 GF(2) 上（加法为异或、乘法为与）给定一个可逆的 $m \times m$ 矩阵 $A$ 和初始向量 $b$。回答 $n$ 组询问，每组给定非负整数 $k$，输出 $A^k b$（其中 $A^0 b = b$）。

## 思路

直接对每个询问做矩阵快速幂需要 $O(m^3 \log k)$，而 $m$ 最大 $1000$，不可接受。本题的关键是：**只针对给定的一个向量 $b$ 建立 Krylov 序列**，而不是对整张矩阵做幂。

### Krylov 序列与最小递推

考虑向量序列：

$$b,\; Ab,\; A^2b,\; \ldots$$

这些向量都在 $m$ 维空间中，最多 $m$ 个线性无关，因此必存在最小的正整数 $d$ 使得 $A^d b$ 可被 $A^0b, \ldots, A^{d-1}b$ 线性表出：

$$A^d b = \sum_{i=0}^{d-1} c_i A^i b$$

这个线性关系对应一个递推多项式 $P(x) = x^d - \sum c_i x^i$，满足 $P(A)b = 0$。

### 高斯消元找递推

逐项生成状态 $state[i] = A^i b$，对每个新向量做“按最高位”的位集高斯消元：

- 若线性无关，加入基，记录它对应的 $A$ 的幂次表达式；
- 若消到零，说明找到了首个线性关系，得到 $d$ 和系数 $c_i$，停止。

### 多项式快速幂

对每个询问，求 $x^k \bmod P(x)$ 的多项式系数（在 GF(2) 上做多项式乘法并对 $P(x)$ 取模），答案就是：

$$A^k b = \sum_i [x^i]\big(x^k \bmod P(x)\big) \cdot A^i b$$

位集让每个多项式乘法只需 $O(d^2/64)$ 的时间。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设 $d$ 为递推阶数，$d \leqslant m$。

- 预处理：生成 $m$ 个状态并消元，位集操作下约为 $O(m^3/64)$。
- 每次询问：多项式快速幂，$O(d^2 \log k / 64)$。

## 总结

不需要显式计算 $m \times m$ 矩阵的幂。只针对给定初始向量建立 Krylov 序列，维数最多为 $m$，用位集高斯消元提取最小递推多项式后，任意高次幂都能通过多项式取模快速求出。这是“线性递推 + 快速幂”思想在向量空间中的推广。