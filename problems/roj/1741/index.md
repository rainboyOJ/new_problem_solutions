---
oj: "roj"
problem_id: "1741"
title: "电子速度"
description: "把叉积平方和展开成 (Σx²)(Σy²)−(Σx·y)²，用树状数组同时维护三个分量，单点改速度与区间询问都是 O(log n)。"
difficulty: "提高"
date: 2026-10-07 20:34
updated: 2026-10-07 20:34
toc: true
tags: ["树状数组", "前缀和", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1741
---

[[TOC]]

## 形式化题目

平面上有 $n$ 个电子，第 $i$ 个电子的速度是向量 $v_i = (x_i, y_i)$，其中 $0 \leqslant x_i, y_i < 20170927$。
"飘升系数"定义为

$$\sum_{1 \leqslant i < j \leqslant n} \bigl|v_i \times v_j\bigr|^2 .$$

需要支持 $m$ 次操作，共两种：

- 修改：给定 $p, x, y$，把 $v_p$ 改成 $(x, y)$；
- 询问：给定 $l \leqslant r$，求 $\displaystyle\sum_{l \leqslant i < j \leqslant r} \bigl|v_i \times v_j\bigr|^2$ 对 $20170927$ 取模的值。

约束：$1 \leqslant n, m \leqslant 10^6$，$1 \leqslant p \leqslant n$，$1 \leqslant l \leqslant r \leqslant n$。

## 正解

### 思路

先把被求的量化开。平面向量叉积只有 $z$ 分量，$|v_i \times v_j| = x_i y_j - x_j y_i$，于是

$$
\begin{aligned}
\sum_{i<j} (x_i y_j - x_j y_i)^2
&= \sum_{i<j} x_i^2 y_j^2 + \sum_{i<j} x_j^2 y_i^2 - 2\sum_{i<j} x_i x_j y_i y_j \\
&= \sum_{i \neq j} x_i^2 y_j^2 - 2\sum_{i<j} (x_i y_i)(x_j y_j).
\end{aligned}
$$

第一个和式是"有序对"求和，可以拆成全体减对角：

$$\sum_{i \neq j} x_i^2 y_j^2 = \Bigl(\sum_i x_i^2\Bigr)\Bigl(\sum_j y_j^2\Bigr) - \sum_i x_i^2 y_i^2 .$$

第二个和式同理，$\sum_{i<j} a_i a_j = \frac{1}{2}\bigl[(\sum a_i)^2 - \sum a_i^2\bigr]$，其中 $a_i = x_i y_i$，代回去正好把 $\sum x_i^2y_i^2$ 抵消：

$$\boxed{\ \sum_{i<j} (x_i y_j - x_j y_i)^2 = \Bigl(\sum_i x_i^2\Bigr)\Bigl(\sum_j y_j^2\Bigr) - \Bigl(\sum_i x_i y_i\Bigr)^2\ }$$

**这一步是整个解法的关键**：它把"两两配对"的二次代价降成了三个**可加**的量。对任意一个下标集合 $S$（特别地，$S = [l, r]$），

$$\text{answer}(S) = P(S) \cdot Q(S) - R(S)^2, \qquad
P = \sum_{i \in S} x_i^2,\quad Q = \sum_{i \in S} y_i^2,\quad R = \sum_{i \in S} x_i y_i .$$

于是问题变成"三个可加量的区间和"：单点修改只会同时改变 $P, Q, R$ 各一处，区间和用前缀和相减得到。

前缀和带单点修改 —— 树状数组。三棵树分别维护 $P, Q, R$，但三个量的修改点和查询点完全一致，
所以合并成一棵树、每个结点同时存三个分量即可：单次修改/询问都是 $O(\log n)$。

**取模细节**。树内每个结点的每个分量恒保存在 $[0, \mathrm{MOD})$：加法后若 $\geqslant \mathrm{MOD}$ 减一次即可
（两个 $< \mathrm{MOD}$ 的数相加 $< 2\mathrm{MOD} < 2^{31}$，不会溢出）。前缀查询把 $\leqslant \log_2 n + 1 = 21$
个这样的值相加，总量 $< 21 \cdot \mathrm{MOD} \approx 4.2 \times 10^8$，仍在 `long long` 内，最后统一取模。
单点修改时增量取 $(\text{新} - \text{旧}) \bmod \mathrm{MOD}$ 归一到非负；答案 $P \cdot Q - R^2$ 中
$P \cdot Q < \mathrm{MOD}^2 \approx 4.07 \times 10^{14}$，`long long` 精确，最后调整符号到 $[0, \mathrm{MOD})$。

注意区间内 $P, Q, R$ 也是"先取模再相乘"的：恒等式两边都是整数，模运算与乘法可交换，结论不变。

### 代码

Python 短解法（同一算法，树状数组用三个列表）：

@include-code(./main.py, python)

C++ 正解（三个分量合并到一棵树状数组，配手写快读快写以承受 $n, m = 10^6$）：

@include-code(./main.cpp, cpp)

### 复杂度

- 时间：初始化 $O(n \log n)$，每次操作 $O(\log n)$，总计 $O((n + m)\log n)$。
- 空间：树状数组与速度数组各 $O(n)$；C++ 约 $24$ MB（$10^6$ 个结点，每结点三个 8 字节分量），Python 约 $5$ 个长度为 $10^6+1$ 的列表。

## 总结

- 遇到"两两配对的平方和 / 叉积和"，先试着把求和式展开成"整体量减对角量"的形式；
  一旦展开成 $P \cdot Q - R^2$ 这种只含**可加量**的表达式，带修区间询问就退化成
  若干条前缀和的维护，树状数组（或线段树）即可。
- 同一个下标集合上的多个可加量，若修改点、查询点相同，可以塞进同一棵树状数组的结点里，
  一次 $\log n$ 走完，不必开三棵树重复遍历。
- 模意义下维护树状数组，只要保证每个结点恒在 $[0, \mathrm{MOD})$（加法后减一次），
  查询时累加量就不会溢出 `long long`。

> **数据说明**：本题所在目录的测试数据由 `data.py` 用 cyaron 生成（生成脚本随素材提供），
> 题面为网络重建版本，与官方原题的数据强度可能略有差异；做法本身即公开题解中流传的
> "三个树状数组"标程思路（叉积平方和 = $(Σx^2)(Σy^2) - (Σxy)^2$）。
