---
oj: "usaco"
problem_id: "1446"
title: "Cake Game"
description: "把博弈转化为 Bessie 保留一个长度 N/2+1 的连续窗口，取窗口和最小值。"
difficulty: "普及/提高-"
date: 2026-07-11 18:32
toc: true
tags: ["博弈", "前缀和", "贪心", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1446
---

[[TOC]]

### 题意

有一排偶数个蛋糕。Bessie 和 Elsie 轮流操作，Bessie 先手：

- Bessie 每次选择相邻两个蛋糕，把它们合并成一个蛋糕；
- Elsie 每次拿走最左边或最右边的一个蛋糕；
- 最后只剩一个蛋糕时，Bessie 吃掉它，Elsie 吃掉所有被她拿走的蛋糕。

两人都最优，求 Bessie 和 Elsie 最终分别吃到多少。

### 思路

先看一个小数据博弈暴力。Bessie 的回合枚举合并哪一对相邻蛋糕并取最大值，Elsie 的回合枚举拿左端或右端并取最小值。

@include-code(./brute.cpp, cpp)

满分做法的关键是看清楚 Elsie 实际能拿走哪些初始蛋糕。

因为 `N` 是偶数：

- Bessie 一共操作 $N/2$ 次；
- Elsie 一共操作 $N/2-1$ 次。

Elsie 每次只能从当前两端拿蛋糕。她可以做到：从原始左端拿 `l` 个蛋糕，从原始右端拿 $N/2-1-l$ 个蛋糕。也就是说，Elsie 可以拿走任意一种“左边若干个 + 右边若干个”的组合，总数量固定为 $N/2-1$。

另一方面，Bessie 可以保护中间的一大块。她第一次合并中间两个蛋糕，之后 Elsie 如果拿走左端，Bessie 就把这个特殊大蛋糕向右合并；Elsie 如果拿走右端，Bessie 就把特殊大蛋糕向左合并。这样 Elsie 永远拿不到这个特殊蛋糕。

所以最终等价于：

- Elsie 会拿走两端总共 $N/2-1$ 个初始蛋糕；
- Bessie 会吃掉中间剩下的一个连续段；
- 这个连续段长度为：

$$
N - (N/2 - 1) = N/2 + 1
$$

Elsie 想让自己总和最大，也等价于让 Bessie 保留的连续段总和最小。

因此答案就是所有长度为 $N/2+1$ 的连续窗口中，窗口和的最小值。

用前缀和可以 $O(1)$ 求任意窗口和。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个测试用例只需要扫描一次数组和所有窗口。

时间复杂度为 $O(N)$，空间复杂度为 $O(N)$。

### 总结

本题表面是博弈，核心却是把双方最优策略转成一个连续窗口问题。

Bessie 能保证最后吃到某个长度 $N/2+1$ 的连续段；Elsie 会让这个连续段尽量小，所以取最小窗口和即可。
