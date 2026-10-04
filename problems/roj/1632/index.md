---
oj: "roj"
problem_id: "1632"
title: "「一本通 6.4 例 2」同余方程"
description: "利用扩展欧几里得算法求解线性同余方程 ax ≡ 1 (mod b) 对应的二元一次不定方程，并调整为最小正整数解。"
difficulty: "入门"
date: 2026-09-30 23:08
updated: 2026-09-30 23:08
toc: true
tags:
  - "数论"
  - "扩展欧几里得"
  - "同余方程"
favorite: false
favorite_reason: ""
categories:
  - "数论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1632
---

[[TOC]]

## 形式化题目

给定两个正整数 $a, b$（$2 \le a, b \le 2 \times 10^9$），且输入保证存在整数解，求同余方程：
$$ax \equiv 1 \pmod b$$
的最小正整数解 $x$。

## 正解

### 思路

同余方程 $ax \equiv 1 \pmod b$ 等价于存在某个整数 $y'$，使得：
$$ax - 1 = -b y' \iff ax + by = 1$$
其中 $y = y'$。由于题目保证一定有解，由裴蜀定理可知 $\gcd(a, b) = 1$。

这转化成了经典的二元一次不定方程求解问题，可以使用**扩展欧几里得算法**（Extended Euclidean Algorithm，简称 `exgcd`）在对数时间内求出一组特解 $(x, y)$：

1. **递归基底**：当 $b = 0$ 时，$\gcd(a, 0) = a$。此时显然有 $a \times 1 + 0 \times 0 = a$，即可取 $x = 1, y = 0$。
2. **递归推进**：设在子问题中，已知 $b x_1 + (a \bmod b) y_1 = \gcd(b, a \bmod b) = \gcd(a, b)$ 的特解 $(x_1, y_1)$。
   因为 $a \bmod b = a - \lfloor a / b \rfloor \cdot b$，代入可得：
   $$b x_1 + \left(a - \left\lfloor \frac{a}{b} \right\rfloor \cdot b\right) y_1 = a y_1 + b \left(x_1 - \left\lfloor \frac{a}{b} \right\rfloor y_1\right) = \gcd(a, b)$$
   对比 $ax + by = \gcd(a, b)$ 的系数，即得到转移式：
   $$\begin{cases} x = y_1 \\ y = x_1 - \lfloor a / b \rfloor y_1 \end{cases}$$

由通解性质可知，若 $x$ 为方程的一个特解，则所有解具有形式 $x' = x + k \cdot b$（$k \in \mathbb{Z}$）。
为了求出**最小正整数解**，只需将 $x$ 调整到 $[1, b]$ 范围。在 Python 中可先进行模运算：
$$x_0 = (x \bmod b + b) \bmod b$$
因为 $b \ge 2$ 且 $a \cdot 0 \equiv 0 \not\equiv 1 \pmod b$，所以 $x_0$ 必落在区间 $[1, b-1]$ 之间，即为所求的最小正整数解。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$\mathcal{O}(\log(\min(a, b)))$。每次辗转相除都会使数值规模大致减半，至多递归约 40 次即可得出结果，运算在毫秒级内完成。
- **空间复杂度**：$\mathcal{O}(\log(\min(a, b)))$。递归调用栈的最大深度由辗转相除的次数决定，占用极少栈空间。

## 总结

求解线性同余方程 $ax \equiv 1 \pmod b$ 是数论中的基础操作（等价于求模逆元）。核心思路是将同余式转化为裴蜀等式 $ax + by = 1$，利用扩展欧几里得算法在 $\mathcal{O}(\log(\min(a, b)))$ 复杂度内递归求出特解，最后通过取模将解平移到最小正整数区间。
