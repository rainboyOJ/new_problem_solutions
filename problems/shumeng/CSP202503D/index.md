---
oj: "shumeng"
problem_id: "CSP202503D"
title: "集体锻炼"
description: "按右端点维护所有不同 gcd 的左端点分组，并用左端点之和一次统计每组区间贡献。"
difficulty: "普及+/提高-"
date: 2026-07-31 16:21
toc: true
tags: ["数论", "gcd", "前缀状态"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503D
---

[[TOC]]

## 形式化题目

给定长度为 $n$ 的序列 $a_1,\dots,a_n$，对每个连续区间 $[l,r]$ 定义价值为 $l \cdot r \cdot \gcd(a_l,\dots,a_r)$，求所有区间价值之和对 $998244353$ 取模的结果。

## 思路

直接枚举 $O(n^2)$ 个区间会超时，关键观察是：固定右端点 $r$，随着左端点向左扩展，区间 $\gcd$ 只会单调不增，且不同的 $\gcd$ 取值只有 $O(\log A)$ 种。

先看朴素的区间枚举：

@include-code(./brute.cpp, cpp)

### 按 gcd 分组

从左向右扫描，把右端点固定为 $r$。维护若干组 $(g, \sum l)$：组内所有区间都以 $r$ 结尾且 $\gcd$ 都等于 $g$，$\sum l$ 是这些区间左端点之和。

加入新元素 $a_r$ 后：

- 新单点区间 $[r,r]$ 的 $\gcd$ 是 $a_r$；
- 旧组的 $\gcd$ 变成 $\gcd(g, a_r)$；
- 相邻且 $\gcd$ 相同的组立即合并，保证每组 $\gcd$ 互不相同。

一组内所有区间的贡献一次算出：

$$
g \times r \times \sum l \pmod{998244353}
$$

### 复杂度来源

每个右端点处 gcd 不同的分组数量为 $O(\log \max a_i)$，因此总复杂度为 $O(n \log A)$。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

每个右端点维护的分组数为 $O(\log A)$，总时间复杂度 $O(n \log A)$，空间复杂度 $O(\log A)$。

## 总结

不要逐个区间重复计算 $\gcd$。把同一右端点下 $\gcd$ 相同的连续左端点合并成组，既保留了 $\gcd$ 值，又用左端点之和 $O(1)$ 处理整组贡献，这是这类区间统计题的经典优化。