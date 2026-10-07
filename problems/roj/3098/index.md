---
oj: "roj"
problem_id: "3098"
title: "「Longge's problem」 龙哥的问题"
description: "求 ∑gcd(i,N)：答案是积性函数，质因数分解后在每个质因子幂 p^a 上乘局部因子 p^(a-1)·(p+a(p-1))，O(√N) 单次求解。"
difficulty: "省选/NOI-"
date: 2026-10-01 16:45
updated: 2026-10-07 13:50
toc: true
tags:
  - "数论"
  - "积性函数"
  - "质因数分解"
  - "欧拉函数"
favorite: false
favorite_reason: ""
categories:
  - "数论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3098
---

[[TOC]]

## 形式化题目

给定正整数 $N$，求 $\sum_{i=1}^{N} \gcd(i, N)$。

## 正解

### 思路

#### 1. 按 gcd 取值分组

$$\sum_{i=1}^{N}\gcd(i,N)=\sum_{d\mid N} d\cdot\#\{i:\gcd(i,N)=d\}=\sum_{d\mid N} d\cdot\varphi(N/d)$$

把 $\gcd = d$ 的 $i$ 归为一组：$\gcd(i,N)=d \iff \gcd(i/d, N/d)=1$，恰好 $\varphi(N/d)$ 个。

#### 2. 积性 + 局部因子

$f(N)=\sum_{d\mid N} d\,\varphi(N/d)$ 是**积性函数**（$d$ 与 $\varphi$ 的狄利克雷卷积）。只需算质因子幂 $N=p^a$ 处的值：

$$f(p^a)=\sum_{k=0}^{a} p^{k}\varphi(p^{a-k}) = p^{a-1}\bigl(p + a(p-1)\bigr)$$

（展开 $\varphi(p^{a-k})=p^{a-k-1}(p-1)$ 等比求和即得。）

于是对 $N=\prod p_i^{a_i}$：

$$f(N)=\prod_i p_i^{a_i-1}\bigl(p_i + a_i(p_i - 1)\bigr)$$

$O(\sqrt N)$ 完成质因数分解，连乘即得答案。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：$O(\sqrt N)$。
- **空间复杂度**：$O(1)$。

## 总结

- 「gcd 之和」类问题的标准变形：按 $\gcd$ 取值分组，化为 $\sum_{d\mid N} d\,\varphi(N/d)$。
- 记住 $f = \mathrm{id} * \varphi$ 是积性函数，质因子幂上的局部因子 $p^{a-1}(p+a(p-1))$ 可直接套用。
- 单个 $N$ 时无需线性筛，$O(\sqrt N)$ 试除分解质因数即可。
