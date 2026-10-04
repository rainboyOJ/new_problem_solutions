---
oj: "roj"
problem_id: "3652"
title: "宝藏"
description: "挖遍所有宝藏屋的最小开发代价：枚举生成树的根分层结构，状压 DP f[S] 表示已开发集合的最小代价，预处理子集连接边权和加速转移，O(3^n·n)。"
difficulty: "省选/NOI-"
date: 2026-10-02 13:20
updated: 2026-10-02 13:42
toc: true
tags:
  - "DP"
  - "状压DP"
  - "状态压缩"
  - "NOIP"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3652
---

[[TOC]]

## 形式化题目

$n$ 个宝藏屋（$n\le 12$）、$m$ 条带权道路。从地面打通到某个宝藏屋代价巨大，而宝藏屋之间开发道路相对便宜；实际模型：选一个根（打通代价 0，按题面给定的「深度系数」加权），再开发若干道路使所有屋连通，最小化总代价（代价 = 每条开发道路的长度 × 所在层的深度系数，按题面约定求和）。

## 正解

### 思路

#### 1. 枚举根 + 分层结构 DP

答案对应的连通结构是一棵以某屋为根的树。固定根 $r$，按 BFS 分层，深度系数 $d_k$ 已知。状态 $S$ = 已开发的屋集合：

$$f[S] = \min_{T \subset S,\ T \text{ 可挂到 } S\setminus T} \bigl(f[S\setminus T] + d_{\text{层}} \cdot w(T, S\setminus T)\bigr)$$

其中 $w(T,U)$ = $T$ 中每个点连到 $U$ 的最短边权和（每个点独立选最短边）。

#### 2. 预处理加速

- `mnd[S][v]`：$v$ 与集合 $S$ 的最短边（去低位增量合并，$O(2^n n)$）；
- `extend[S]`：枚举 $S$ 的子集 $T$ 并求连接权和，总工作量 $O(3^n n)$。

对每个根跑 DP 取最小，$n\le 12$ 时限内可行（根可以只枚举每个连通分量代表以加速）。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(3^n \cdot n)$（预处理）+ $O(2^n \cdot 2^n)$ 转移量级，$n\le 12$ 可过。
- **空间复杂度**：$O(2^n \cdot n)$。

## 总结

- 「选根 + 分层开发」的最小代价 = 枚举根的**子集划分 DP**。
- 子集枚举总量 $3^n$ 是此类题的标准规模，预处理 `mnd`/`extend` 把转移摊薄。
- $n\le 12$ 是状压 DP 的典型信号。
