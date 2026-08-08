---
oj: "luogu"
problem_id: "P1593"
title: "因子和"
description: "分解 a 的质因数，把 a^b 的因子和化成等比数列乘积，并用分治同时求幂与前缀和。"
difficulty: "普及+/提高"
date: 2026-01-01 09:14
toc: true
tags: ["数论", "质因数分解", "分治", "因子和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1593
---

[[TOC]]

### 题意

求 `a^b` 的所有正因子之和，对 `9901` 取模。

### 思路

若 $a=\prod p_i^{c_i}$，则 $a^b=\prod p_i^{c_i b}$。每个约数可以独立选择每个质因子的指数，所以因子和为：

$$\prod_i(1+p_i+p_i^2+\cdots+p_i^{c_i b})$$

不能无条件使用等比数列除法，因为 `p-1` 可能在模 `9901` 下没有逆元。代码用分治函数返回前 `terms` 项所需的两个量：

```text
(p^terms, 1+p+...+p^(terms-1))
```

已知一半的幂 `power` 和和 `total`，偶数项可合并成 `total*(1+power)`；奇数项再补最后一个幂。递归深度只有 $O(\log terms)$，且完全不需要除法。

### Python 知识

- 函数返回二元组，同时复用分治计算出的幂和等比和。
- Python 的递归深度在这里安全，因为指数最多带来几十层二分。
- 每次乘法立即 `% MOD`，控制中间整数大小。
- `count*exponent+1` 是等比数列的项数，不是最高指数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度和整数取模。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：把各质因子贡献归约成乘积。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

分解 `a` 需要 $O(\sqrt a)$，每个质因子的等比和需要 $O(\log(cb))$；额外空间是分治递归栈 $O(\log b)$。

### 总结

唯一分解把因子和拆成等比数列乘积；用“幂与和一起算”的分治形式，可以避开模逆元的特殊情况。
