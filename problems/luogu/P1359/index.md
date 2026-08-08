---
oj: "luogu"
problem_id: "P1359"
title: "租用游艇"
description: "把出租站看成 DAG 上的点，按编号顺序做最短路/动态规划，转移到所有更下游的站点。"
difficulty: "普及-"
date: 2026-06-19 11:10
toc: true
tags: ["dp", "最短路", "动态规划"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1359
---

[[TOC]]

### 题意

有 `n` 个游艇站点。

可以从任意站点 `i` 直接租到任意更下游的站点 `j`，费用为 `r[i][j]`。

要求求出从 `1` 号站到 `n` 号站的最少租金。

### 思路

最直接的教学版做法是搜索所有可能的租船路线：

@include-code(./brute.cpp, cpp)

但这题其实可以直接做 DP。

把每个站点看成一个点，从 `i` 向所有 `j > i` 连边，边权是租金。

由于边只会从小编号走向大编号，所以这是一张 DAG。

设 `dp[i]` 表示从 `1` 到 `i` 的最少租金，那么：

`dp[j] = min(dp[j], dp[i] + cost[i][j])`

按编号顺序从小到大转移就行。

#### DP 公式

设 $dp_i$ 表示从码头 $1$ 到码头 $i$ 的最少租金。初始化：

$$
dp_1=0,\quad dp_i=+\infty\ (i>1)
$$

若可以从 $i$ 直接租船到 $j$，费用为 $cost_{i,j}$，则：

$$
dp_j=\min(dp_j,\ dp_i+cost_{i,j})
$$

最终答案为：

$$
dp_n
$$


公式解释：`dp_i` 保存已经到达码头 `i` 的最小费用。若再租一段从 `i` 到 `j` 的船，就能用 `dp_i + cost_{i,j}` 更新 `dp_j`；码头编号天然从小到大，形成无环转移。


### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(n^2)$

### 总结

这题虽然看起来像图论题，但因为图本身就是按编号单向向下的，所以直接按编号做 DP 最简单。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
