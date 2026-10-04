---
oj: "roj"
problem_id: "1659"
title: "「一本通 6.6 练习 8」礼物"
description: "扩展 Lucas 定理（exLucas）求组合数模任意合数：按质因数幂分拆模数，抽干 p 因子后分块阶乘求 C mod p^k，再用 CRT 拼回答案。"
difficulty: "省选/NOI-"
date: 2026-10-01 00:30
updated: 2026-10-01 01:22
toc: true
tags:
  - "数论"
  - "扩展 Lucas"
  - "中国剩余定理"
  - "组合数"
favorite: false
favorite_reason: ""
categories:
  - "数论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1659
---

[[TOC]]

## 形式化题目

购买 $n$ 件礼物送给 $m$ 个人，第 $i$ 人至少收 $w_i$ 件。求分配方案数模 $P$（$P \le 10^9$，不保证是素数）；若 $\sum w_i > n$ 则输出 `Impossible`。

## 正解

### 思路

#### 1. 乘法拆解：顺序选人

依次给每个人挑礼物，第 $i$ 人从剩余礼物中选 $w_i$ 件，方案总数为连乘：

$$\binom{n}{w_1}\binom{n - w_1}{w_2}\cdots\binom{n - w_1 - \cdots - w_{m-1}}{w_m}$$

每个人挑完即确定（人选有标号、礼物无标号），乘起来就是答案。判无解只需 $\sum w_i > n$。

#### 2. 模数是合数：扩展 Lucas

普通 Lucas 只适用于**素数**模。$P \le 10^9$ 是合数时，标准做法 **exLucas**：

1. 把 $P$ 分解为质因数幂 $P = \prod p_i^{k_i}$（试除到 $\sqrt{P}$ 即可）；
2. 对每个 $p^k$ 单独求 $C(n, m) \bmod p^k$；
3. 用 **CRT（中国剩余定理）** 把各 $p^k$ 下的余数拼回模 $P$ 的唯一解。

#### 3. 求 C(n, m) mod p^k 的关键：抽干 p 因子

$p$ 不再可逆（分母含 $p$ 时逆元不存在），处理分三步：

- **指数分离**：用勒让德公式算出 $C(n,m)$ 中 $p$ 的总指数 $e$（对 $n!, m!, (n-m)!$ 分别累加 $\lfloor x/p \rfloor + \lfloor x/p^2 \rfloor + \cdots$ 后相减）；
- **p-free 阶乘**：把 $n!$ 中所有 $p$ 的因子抽掉后剩下的部分模 $p^k$。利用周期性**分块**：$1 \dots p^k$ 内与 $p$ 互素的数乘积作为一个"整块"复用，剩余零头单独算；
- **合成**：$C(n,m) \equiv p^e \cdot \text{unit} \pmod{p^k}$。若 $p^e$ 已是 $p^k$ 的倍数则直接为 $0$。

Python 的 `pow(x, -1, pk)` 保证模逆元存在（$x$ 与 $p$ 互素时），支撑 p-free 部分的除法。

#### 4. CRT 合并

模数两两互素，逐个合并方程 `res += (a - res) * inv(M, q) * M`，把模 $M$ 的解抬升到模 $Mq$ 且对 $q$ 也取到余数 $a$，最终 $res \bmod P$ 即答案。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：分解 $P$ 为 $O(\sqrt P)$；每个质因数幂的 exLucas 为 $O(p^k + \log n)$（p-free 分块枚举 $p^k$ 以内互素数），总体对 $P \le 10^9$ 完全可行。
- **空间复杂度**：$O(\log P)$，仅存质因数幂表。

## 总结

- 本题是 exLucas 标准模板：「组合数连乘 + 合数模」的完整流程——质因数分解、抽干 $p$ 因子、分块 p-free 阶乘、CRT 合并。
- 与素数模 Lucas（1656 Combination）形成对照：模数不再是素数时，必须在 $p^k$ 下手工处理不可逆的分母。
- 无解判定 $\sum w_i > n$ 简单但必要；连乘拆解把"多约束分配"化为一串独立组合数。
