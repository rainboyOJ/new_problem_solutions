---
oj: "luogu"
problem_id: "P1352"
title: "没有上司的舞会"
description: "用树形 DP 维护每个员工选与不选两种状态，父子不能同时选择。"
difficulty: "普及/提高-"
date: 2026-06-22 22:59
toc: true
tags: ["树形DP", "动态规划", "树"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1352
---

[[TOC]]

### 题意

给定一棵上下级关系树，每个员工有快乐值。

不能同时邀请一个员工和他的直接上司，求最大快乐值。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力枚举每个人参加或不参加会有 `2^n` 种方案。树上父子限制适合用树形 DP。

定义：

```text
dp[u][0] = 不邀请 u 时，u 子树内最大快乐值
dp[u][1] = 邀请 u 时，u 子树内最大快乐值
```

若不邀请 `u`，每个孩子可以来，也可以不来：

```text
dp[u][0] += max(dp[v][0], dp[v][1])
```

若邀请 `u`，所有直接孩子都不能来：

```text
dp[u][1] += dp[v][0]
```

最后答案是：

```text
max(dp[root][0], dp[root][1])
```

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个点处理一次，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

树形 DP 的第一步是想清楚“父节点如何影响子节点”。

本题中影响只有一种：父亲来了，孩子不能来，所以每个点用“选/不选”两个状态即可。
