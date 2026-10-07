---
oj: "roj"
problem_id: "1658"
title: "「一本通 6.6 练习 7」超能粒子炮 · 改"
description: "利用 Lucas 定理按 p 进制将组合数前缀和拆分为整块与散块，递归计算 S(n, k) mod 2333"
difficulty: "提高+/省选-"
date: 2026-10-01 00:22
updated: 2026-10-07 13:50
toc: true
tags:
  - "数论"
  - "Lucas 定理"
  - "组合数学"
  - "前缀和"
favorite: false
favorite_reason: ""
categories:
  - "数学"
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1658"
---

[[TOC]]

## 形式化题目

给定常数质数 $p = 2333$。有 $T$ 组询问，每次给定非负整数 $n, k$，求组合数前缀和：

$$S(n, k) = \sum_{i=0}^k \binom{n}{i} \pmod{2333}$$

## 正解

### 思路

根据 Lucas 定理，对于质数 $p$ 和任意非负整数 $n, i$，有：

$$\binom{n}{i} \equiv \binom{\lfloor n/p \rfloor}{\lfloor i/p \rfloor} \binom{n \bmod p}{i \bmod p} \pmod p$$

我们要求的是前缀和：

$$S(n, k) = \sum_{i=0}^k \binom{n}{i} \pmod p$$

将求和变量 $i$ 进行带余除法：设 $i = j \cdot p + r$，其中 $0 \le r < p$。由于 $0 \le i \le k$，可将商 $j$ 分成两部分考虑：

1. **完整块（$0 \le j \le \lfloor k/p \rfloor - 1$）**：
   在每一个固定的 $j$ 下，余数 $r$ 取遍了完整区间 $[0, p-1]$。利用 Lucas 定理将组合数因式分解：

   $$\sum_{r=0}^{p-1} \binom{n}{j \cdot p + r} \equiv \binom{\lfloor n/p \rfloor}{j} \sum_{r=0}^{p-1} \binom{n \bmod p}{r} = \binom{\lfloor n/p \rfloor}{j} S(n \bmod p, p-1) \pmod p$$

   对所有合法的 $j$ 求和，提取公因式 $S(n \bmod p, p-1)$：

   $$\sum_{j=0}^{\lfloor k/p \rfloor - 1} \left( \binom{\lfloor n/p \rfloor}{j} S(n \bmod p, p-1) \right) = S(n \bmod p, p-1) \cdot S\left(\lfloor n/p \rfloor, \lfloor k/p \rfloor - 1\right) \pmod p$$

2. **不完整散块（$j = \lfloor k/p \rfloor$）**：
   此时商固定为 $\lfloor k/p \rfloor$，余数 $r$ 只能取到 $0 \le r \le k \bmod p$。其贡献为：

   $$\binom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor} \sum_{r=0}^{k \bmod p} \binom{n \bmod p}{r} = \binom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor} \cdot S(n \bmod p, k \bmod p) \pmod p$$

将两部分合并，即可得到核心递归公式：

$$S(n, k) \equiv S(n \bmod p, p-1) \cdot S\left(\lfloor n/p \rfloor, \lfloor k/p \rfloor - 1\right) + \binom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor} \cdot S(n \bmod p, k \bmod p) \pmod p$$

#### 算法流程

1. **预处理**：模数 $p = 2333$ 很小，利用杨辉三角预处理出 $p \times p$ 的组合数表 $C(n, m) \pmod p$ 和每行前缀和表 $S(n, m) \pmod p$。
2. **递归计算**：
   - 递归边界：若 $k < 0$，返回 $0$；若 $n < p$ 且 $k < p$，直接查表返回 $S[n][k]$。
   - 转移时调用自身计算更小规模的 $S(\lfloor n/p \rfloor, \lfloor k/p \rfloor - 1)$，并用 Lucas 定理单次查询 $\binom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor}$。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：
  - 预处理表格：时间复杂度为 $O(p^2) = 2333^2 \approx 5.4 \times 10^6$ 次运算。
  - 单次查询：每层递归规模以 $p$ 为底对数缩小，递归深度为 $\lfloor \log_p n \rfloor$。由于 $p = 2333, n \le 10^{18}$，递归层数最多不超过 $6$ 层。每次递归需要一次 $O(\log_p n)$ 的 Lucas 组合数求值与一次子问题递归调用，单次查询时间复杂度为 $O(\log_p^2 n)$。
  - 总时间复杂度为 $O(p^2 + T \log_p^2 n)$。
- **空间复杂度**：预处理存储 $p \times p$ 的组合数表和前缀和表，空间复杂度为 $O(p^2)$。

## 总结

本题是 Lucas 定理在组合数前缀和求值中的经典应用。通过将下标 $i$ 按模 $p$ 进行整块与散块分解，巧妙地将上指标与下指标同时缩小除以 $p$，从而把原本 $O(k)$ 的不可行前缀求和优化为 $O(\log_p^2 n)$ 的分治递归。
