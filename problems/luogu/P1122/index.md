---
oj: "luogu"
problem_id: "P1122"
title: "最大子树和"
description: "用树形 DP 计算必须保留每个点时的最大连通块权值，负贡献子树直接剪掉。"
difficulty: "普及/提高-"
date: 2026-06-22 23:07
updated: 2026-10-03 12:38
toc: true
tags: ["树形DP", "动态规划", "树"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P1115"
    reason: "A 教的「以 i 结尾/必须包含当前元素」状态设计与「负贡献就不接」取舍，被 B 逐孩子复用成 dp[u]=beauty[u]+sum(max(0,dp[v]))（main.cpp 中 if (dp[v] > 0) dp[u] += dp[v]），只是把一行序列换成了树上后序遍历"
  - oj: "luogu"
    problem_id: "P3009"
    reason: "B 的树形 DP 直接复用 A 教的「状态必须包含当前元素 + 前面的负贡献不接」这一步：A 在序列上写成 dp[i]=max(a[i],dp[i-1]+a[i]) 并在 dp[i-1] 是负贡献时重新起头，B 把它逐孩子套成 dp[u]=beauty[u]+sum(max(0,dp[v]))（main.cpp 的 if (dp[v] > 0) dp[u] += dp[v]），再用同一句「最终答案是所有 dp 中的最大值」收尾，额外叠加的只是树上后序 DFS 与父节点去重，难度只提高一级。"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1122
---

[[TOC]]

### 题意

给定一棵树，每个点有一个美丽指数，可以通过剪枝保留一个非空连通块。

要求保留下来的连通块点权和最大。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力枚举所有连通点集不可行。考虑树形 DP。

任选一个根。定义：

```text
dp[u] = 必须保留 u，并且只在 u 的子树内选择连通块时的最大点权和
```

如果孩子 `v` 的 `dp[v]` 是正数，把它接到 `u` 上会让答案变大；如果是负数，就剪掉这个子树更好。

所以转移是：

```text
dp[u] = beauty[u] + sum(max(0, dp[v]))
```

最终答案是所有 `dp[u]` 中的最大值。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

这道题的核心就是“负贡献剪掉”。

树上每个孩子方向互不影响，只要保留正贡献的子树，就能得到包含当前点的最优连通块。
