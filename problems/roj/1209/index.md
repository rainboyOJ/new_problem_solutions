---
oj: "roj"
problem_id: "1209"
title: "分数求和"
description: "逐次通分相加并立即用 gcd 约分，保持最简后按整数或分数格式输出。"
difficulty: "入门"
date: 2026-09-29 23:39
updated: 2026-09-29 23:39
toc: true
tags: ["模拟", "gcd", "分数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1209"
---

[[TOC]]

## 形式化题目

给定 $n$（$1 \leqslant n \leqslant 10$）个正分数 $\frac{p_i}{q_i}$（$1 \leqslant p_i, q_i \leqslant 10$），求它们之和的最简表示；若分母为 $1$，则只输出整数。

## 正解

### 思路

用整数二元组 $(a, b)$ 保存当前累加和。读入每个分数 $p/q$ 后，按

$$
\frac{a}{b} + \frac{p}{q} = \frac{a \cdot q + b \cdot p}{b \cdot q}
$$

通分相加，再用 $\gcd$ 约去分子分母的最大公约数，使分数保持最简。全部相加后，若分母为 $1$ 就只输出整数。

### 样例推演

| 步骤 | 当前分数 | 新分数 | 约分后 |
| --- | --- | --- | --- |
| 初始 | $0/1$ | — | $0/1$ |
| $+1/2$ | $0/1$ | $2/2$ | $1/2$ |
| $+1/3$ | $1/2$ | $5/6$ | $5/6$ |

最终输出 `5/6`。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \cdot \log C)$，$C$ 为中间分子分母量级；$n \leqslant 10$，实际开销极小。
- 空间复杂度：$O(1)$。

## 总结

分数求和的本质是有理数加法。只要每次相加后立即约分，就能在极小数据范围内稳定得到最简结果。
