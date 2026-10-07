---
oj: "roj"
problem_id: "1656"
title: "「一本通 6.6 练习 5」Combination"
description: "Lucas 定理求组合数取模：预处理阶乘与逆元，把 C(n,m) mod p 按 p 进制拆成各位小组合数的乘积，用费马小定理求逆元。"
difficulty: "提高+/省选-"
date: 2026-10-01 00:18
updated: 2026-10-07 13:50
toc: true
tags:
  - "数论"
  - "Lucas 定理"
  - "组合数"
  - "费马小定理"
favorite: false
favorite_reason: ""
categories:
  - "数论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1656
---

[[TOC]]

## 形式化题目

$t$ 组询问，每组给出 $n, m$，求组合数 $\binom{n}{m} \bmod 10007$ 的值。

## 正解

### 思路

#### 1. 模数是素数：Lucas 定理登场

模数 $p = 10007$ 是**素数**。当 $n$ 很大（本题 $n$ 可远超 $p$）而模数是小素数时，直接对阶乘取模求组合数会因 $n!$ 含因子 $p$ 而失效（逆元不存在）。此时用 **Lucas 定理**：

$$\binom{n}{m} \equiv \prod_{i} \binom{n_i}{m_i} \pmod p$$

其中 $n_i, m_i$ 是 $n, m$ 的 **$p$ 进制展开**各位数字。每个因子 $\binom{n_i}{m_i}$ 的上下参数都小于 $p$，可直接用预处理的阶乘 + 逆元在 $O(1)$ 求出；若某位 $m_i > n_i$，整个乘积为 $0$。

#### 2. 小组合数的 O(1) 求法

预处理 $p$ 以内阶乘表 $F[i] = i! \bmod p$。对 $n, m < p$：

$$\binom{n}{m} \equiv F[n] \cdot (F[m] \cdot F[n-m])^{-1} \pmod p$$

分母的逆元用**费马小定理**：$x^{-1} \equiv x^{p-2} \pmod p$，Python 内置 `pow(x, -1, p)` 即可一步求出。

#### 3. 实现要点

- 阶乘表只需 $p = 10007$ 项，一次预处理，所有询问共用；
- Lucas 按 $p$ 进制逐位拆解：`while n or m: 取 n%p, m%p 对应因子；n //= p; m //= p`；
- 每组询问 $O(\log_p n)$，配合 $O(1)$ 的单因子查询，总复杂度极低。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：预处理 $O(p)$；每组询问 $O(\log_p n)$，总 $O(p + t \log_p n)$。
- **空间复杂度**：$O(p)$，阶乘表共 $10007$ 项。

## 总结

- 「大 $n$ 小素数模」组合数的标准解法就是 Lucas 定理：$p$ 进制拆位，把大组合数化为若干小组合数的乘积。
- 费马小定理 + Python 的 `pow(x, -1, p)` 让模逆元实现只需一行。
- 预处理阶乘表是所有询问共享的固定成本，整个程序 IO 之外几乎全是查表。
