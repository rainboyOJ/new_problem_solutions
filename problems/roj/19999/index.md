---
oj: "roj"
problem_id: "19999"
title: "Function"
description: "f(i,j) 是 y_i、y_j 的加权平均，取值有界可二分；f(i,j)≥v 变形为两个序列的比较，排序后双指针 O(n) 计数求第 k 大。"
difficulty: "普及+/提高-"
date: 2026-08-28 19:55
toc: true
tags: ["二分答案", "双指针", "排序"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/19999
---

[[TOC]]

## 形式化题目

给定 $n$ 个点 $(x_i, y_i)$，对每对 $1 \leqslant  i < j \leqslant  n$ 定义

$$f(i,j)=\frac{x_i y_i + x_j y_j}{x_i + x_j}$$

共有 $\frac{n(n-1)}{2}$ 个值。把它们从大到小排序，求第 $k$ 大的元素。

## 思路

一句话本质：$f(i,j)$ 是 $y_i, y_j$ 关于权重 $x_i, x_j$ 的加权平均，所以取值有界、可二分；"第 $k$ 大"用二分答案 $v$ 转化，而 $f(i,j) \geqslant v$ 可以变形为两个独立序列之间的比较 $x_i(y_i-v) \geqslant x_j(v-y_j)$，排序后双指针 $O(n)$ 计数。

**问题？**直接枚举所有 $f(i,j)$ 排序取第 $k$ 个可行吗？

$n = 10^5$ 时有约 $5 \times 10^9$ 个 $f(i,j)$ 值，既存不下也排不完。但小数据下这是最直观的朴素解，先看它：

@include-code(./brute.cpp, cpp)

这个暴力双重循环枚举每一对数对 $(i,j)$，算出全部 $f(i,j)$ 降序排序后取第 $k$ 个，$O(n^2 \log n)$，只适合小数据。

**问题？**"第 $k$ 大"这类问题有什么通用套路？

要么显式求出前 $k$ 大的值，要么二分答案 $v$ 后统计"有多少个值 $\geqslant v$"。这里 $k$ 最大约 $5 \times 10^9$，求前 $k$ 大不可行，只能二分。二分需要两个前提：答案有界、计数够快。

**问题？**$f(i,j)$ 的取值为什么有界？

$f(i,j)=\dfrac{x_i y_i + x_j y_j}{x_i+x_j}$ 恰好是 $y_i, y_j$ 以 $x_i, x_j$ 为权重的加权平均，所以它介于 $\min(y_i,y_j)$ 与 $\max(y_i,y_j)$ 之间。由 $1 \leqslant y_i \leqslant 10^9$ 知 $f(i,j)$ 恒在 $[1, 10^9]$，二分区间可取 $[1, 10^9]$。

**问题？**怎么快速统计 $f(i,j) \geqslant v$ 的对数？

两边乘正数 $x_i+x_j$ 后移项：

$$x_i y_i + x_j y_j \geqslant v x_i + v x_j \iff x_i(y_i-v) \geqslant x_j(v-y_j)$$

令 $p_i = x_i(y_i-v)$、$q_j = x_j(v-y_j)$，条件变成 $p_i \geqslant q_j$：两个各自独立的序列，问题转化为统计 $p_i \geqslant q_j$ 的有向对数。

**问题？**统计 $p_i \geqslant q_j$ 的对数怎么做到 $O(n)$？

把 $p, q$ 分别升序排序，双指针：$p$ 升序时 $p[i]$ 单调不减，满足 $q[j] \leqslant p[i]$ 的 $j$ 是前缀且长度单调不减，两个指针各至多移动 $n$ 次。注意这是有向计数：$(i,j)$ 与 $(j,i)$ 各算一次，每个合法无序对恰好贡献 2 次；还要减掉 $i = j$ 的自我配对（$p_i \geqslant q_i \iff p_i \geqslant 0$ 时被多计一次，须在排序前用原始下标判断），最后除以 2 才是无序对数。

**实现细节**：`check` 里的浮点比较用 $10^{-3}$ 容差代替严格的 $\geqslant$（如 `q[j] - p[i] < 1e-3` 视为 $q_j \leqslant p_i$），避免二分边界附近的表示误差造成误判；题目只要求答案精确到 $10^{-2}$，该容差足够安全。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

二分约 40 次（区间 $[1,10^9]$ 收敛到 $10^{-3}$），每次 `check` 排序 $O(n \log n)$、双指针 $O(n)$，总复杂度 $O(n \log n \log V)$，$V = 10^9$；空间 $O(n)$。最大数据实测约 0.58s，远低于 2s 时限。

## 总结

- 核心观察一：$f(i,j)$ 是加权平均，天然有界，二分区间 $[1, 10^9]$ 成立；
- 核心观察二："第 $k$ 大"用"二分答案 + 计数 $\geqslant v$ 的对数"解决，$k$ 大到无法求前 $k$ 大；
- 核心观察三：不等式分离变量，$f(i,j) \geqslant v \iff p_i \geqslant q_j$，两序列排序后双指针 $O(n)$ 计数；
- 实现易错点：$k$ 用 `long long`；自我配对修正必须在排序前按原始下标做；双指针先判下标再访问。
