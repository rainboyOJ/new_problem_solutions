---
oj: "POJ"
problem_id: "2976"
title: "Dropping tests"
difficulty: "普及+/提高"
date: 2026-01-05 15:01
updated: 2026-10-07 12:15
toc: true
tags: ["01分数规划"]
desc: "01分数规划入门题"
pre:
common:
  - oj: "luogu"
    problem_id: "P4951"
    reason: "同为 01 分数规划：二分比值 x 并把分式判定转为 Σ(参数+x·参数) 的线性判定；差别只在验证结构（2976 取最大 n-k 项求和，P4951 求最小生成树）。"
  - oj: "luogu"
    problem_id: "P3199"
    reason: "同为分数规划问题，POJ 2976 用贪心排序验证，P3199 用 SPFA 判负环验证，对比不同检验手段。"
source: https://vjudge.net/problem/POJ-2976#author=Aurora5090
---

[[TOC]]

## 题目解析

**题意**：有 $n$ 次考试，第 $i$ 次得了 $a_i$ 分（满分 $b_i$ 分）。允许丢掉其中 $k$ 次，使剩下 $n-k$ 次的累计平均分 $100 \cdot \dfrac{\sum a_i}{\sum b_i}$ 尽可能大，输出四舍五入到整数的最大百分比。

### 1. 二分性（单调性）

- **二分性**：如果分数 $x$ 可以达到，那么比 $x$ 更小的分数都能达到（沿用同一组考试即可）。即 $query_{max\_sum}(x) \geqslant 0$ 成立时，任意 $x_i < x$ 也都成立。因此可以对答案 $x$ 本身二分，我们要让 $x$ 尽可能大。
- **答案范围**：$[0, 1]$（输出时再乘 100）。

于是问题变成：给定 $x$，判定「是否存在一种丢弃方案，使平均分至少为 $x$」。

### 2. 分数规划变形（关键观察）

验证 $x$ 可达，就是问是否存在一组 $S$（$|S| = n-k$）满足：

$$
\frac{\sum_{i \in S} a_i}{\sum_{i \in S} b_i} \geqslant x
$$

两边乘正数 $\sum_{i \in S} b_i$，并按考试 $i$ 整理：

$$
\sum_{i \in S} (a_i - x \cdot b_i) \geqslant 0
$$

定义 $v_i = a_i - x \cdot b_i$，「比率 $\geqslant x$」就被转成「选出的 $v_i$ 之和 $\geqslant 0$」。这一步是 01 分数规划的灵魂：把分式判定变成线性求和判定，把分子分母联动的困难消掉。

### 3. check 函数：贪心取最大的 $n-k$ 个

要让 $\sum v_i$ 尽可能大，显然应该选 $v_i$ 最大的 $n-k$ 个。若它们的和仍然 $< 0$，任何选法都不可能达到 $x$；否则 $x$ 可达（甚至可能更高）。

代码对应：`_sum(x)` 计算所有 $v_i$、排序后累加末尾 $n-k$ 个；`check(mid)` 返回 `_sum(mid) >= 0`。

### 4. 二分与输出

- 在 $[0, 1]$ 上固定二分 100 次：每次取 $mid = (l+r)/2$，`check(mid)` 为真则 `l = mid`，否则 `r = mid`。100 次后区间长度缩到 $2^{-100}$，远超输出精度需要。
- 最后输出 `(int)(l*100 + 0.5)`，即四舍五入后的百分比。

### 5. 复杂度

每次 check 需要 $O(n \log n)$ 排序，二分固定 100 次，总计 $O(100 \cdot n \log n)$；额外空间 $O(n)$ 存放 $v_i$。

## 代码 

@include-code(./1.cpp, cpp)

