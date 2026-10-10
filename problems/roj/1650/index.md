---
oj: "roj"
problem_id: "1650"
title: "「一本通 6.6 例 3」组合"
description: "利用 Lucas 定理将大组合数按质数模数 p 分解为 p 进制位，结合快速幂与逆元计算 C(n, m) mod p。"
difficulty: "提高"
date: 2026-09-30 23:55
updated: 2026-10-07 13:50
toc: true
tags:
  - 数论
  - 组合数学
  - Lucas定理
favorite: false
favorite_reason: ""
categories:
  - 数论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1650
---

[[TOC]]

## 形式化题目

给定 $T$ 组询问，每组给出三个正整数 $n, m, p$（其中 $p$ 为质数，且满足 $1 \leqslant m \leqslant n \leqslant 10^9$，$m \leqslant 10^4$，$m < p < 10^9$）。
求：
$$\binom{n}{m} \bmod p$$

## 正解

### 思路

当 $n \geqslant p$ 时，组合数 $\binom{n}{m} = \frac{n!}{m!(n-m)!}$ 的分子分母展开式中可能包含模数 $p$ 的倍数，直接求逆元会遇到分母与模数不互质的问题。对于模数 $p$ 为质数的场景，可使用 **Lucas 定理**进行转化。

Lucas 定理指出，对于任意非负整数 $n, m$ 与质数 $p$：
$$\binom{n}{m} \equiv \binom{n \bmod p}{m \bmod p} \times \binom{\lfloor n/p \rfloor}{\lfloor m/p \rfloor} \pmod p$$

从进制的角度来看，相当于将 $n$ 与 $m$ 表示为 $p$ 进制展开：
$$n = \sum_{i=0}^k a_i p^i,\quad m = \sum_{i=0}^k b_i p^i \quad (0 \leqslant a_i, b_i < p)$$
则原组合数在模 $p$ 意义下等价于各位组合数的乘积：
$$\binom{n}{m} \equiv \prod_{i=0}^k \binom{a_i}{b_i} \pmod p$$

对于每一位的小组合数 $\binom{a_i}{b_i} \bmod p$：
1. 若 $a_i < b_i$，则方案数为 $0$，整体答案直接为 $0$；
2. 若 $a_i \geqslant b_i$，因为题设保证 $m \leqslant 10^4$，所以 $b_i \leqslant m \leqslant 10^4$ 的规模很小。
   我们可以直接将分子 $a_i \times (a_i - 1) \times \dots \times (a_i - b_i + 1)$ 与分母 $1 \times 2 \times \dots \times b_i$ 分别连乘取模。由于 $p > m \geqslant b_i$ 且 $p$ 为质数，分母中所有数与 $p$ 互质，利用费马小定理通过快速幂计算分母模 $p$ 的逆元 $\text{den}^{p-2} \bmod p$ 即可完成单项计算。

整体使用迭代循环提取 $p$ 进制位，逐步乘入总结果中。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：
  将 $n, m$ 转换为 $p$ 进制位需要 $O(\log_p n)$ 步。每一位计算小组合数时，连乘项数不超过 $m$ 项，求逆元耗时 $O(\log p)$。
  因此单组数据时间复杂度为 $O(m \log_p n + \log p)$。由于 $m \leqslant 10^4$ 且 $p > m$，在极限情况下运算量也非常小，总时间复杂度为 $O(T(m \log_p n + \log p))$。
- **空间复杂度**：
  仅需存储常数个临时变量，辅助空间复杂度为 $O(1)$。

## 总结

当组合数 $\binom{n}{m}$ 中 $n$ 极大且模数 $p$ 为质数时，Lucas 定理提供了将大范围组合数降维到模数以内的标准桥梁。利用 $p$ 进制按位拆分，将大问题转化为若干小组合数的乘积，再结合逆元与快速幂即可高效求解。
