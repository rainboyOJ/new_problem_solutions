---
oj: "luogu"
problem_id: "P1395"
title: "会议"
description: "用子树大小和换根 DP 递推每个点的距离和，取距离和最小且编号最小的点作为会议地点。"
difficulty: "普及"
date: 2026-07-16 23:59
toc: true
tags: ["换根 DP", "树形 DP", "树"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1395
---

[[TOC]]

## 形式化题目

给定一棵 $n$ 个点、$n-1$ 条边的无向树，每条边长度都是 $1$。对每个点 $x$，记

$$S(x) = \sum_{u=1}^{n} \mathrm{dist}(u, x)$$

即所有点到 $x$ 的距离和。要求找出使 $S(x)$ 最小的点，输出它的编号与 $S(x)$；若有多个点同样最小，输出编号最小的那个。

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 枚举每个点作为会议地点，对每个点各做一次 BFS 求距离和，复杂度 $O(n^2)$，无法通过 $n = 5 \times 10^4$。

关键观察是**相邻两点换根时，距离和可以 $O(1)$ 转移**。先把树以 $1$ 为根，算出每个点的子树大小 `subtree_size[u]` 和以 $1$ 为会议地点时的距离和 `dist_sum[1]`（它等于所有点的深度之和）。设 $v$ 是 $u$ 的儿子，会议地点从 $u$ 移到 $v$ 时：

- $v$ 子树内的 `subtree_size[v]` 个点，路径不再经过边 $(u,v)$，距离各减少 $1$；
- 其余 $n - \mathrm{subtree\_size}[v]$ 个点，路径要多经过边 $(u,v)$，距离各增加 $1$。

所以换根公式为：

$$\mathrm{dist\_sum}[v] = \mathrm{dist\_sum}[u] + n - 2 \cdot \mathrm{subtree\_size}[v]$$

按 BFS 遍历序从根向叶子走一遍，每个点的距离和都算出来了，最后扫描取最小即可。

### 数学视角：距离和最小的点就是树的重心

换根公式里，移动方向由 $n - 2 \cdot \mathrm{subtree\_size}[v]$ 的符号决定：

- 若 $\mathrm{subtree\_size}[v] > n/2$，移到 $v$ 会**减小**距离和；
- 若 $\mathrm{subtree\_size}[v] < n/2$，移到 $v$ 会**增大**距离和；
- 若恰好等于 $n/2$，移到 $v$ 距离和不变。

因此距离和最小的点正是删掉它后所有连通块大小都不超过 $n/2$ 的**重心**。这道题不必显式求重心，直接按公式递推每个点的距离和即可；这个观察同时验证了算法的正确性。

以样例链 $1 - 2 - 3 - 4$ 为例，以 $1$ 为根做一次换根 DP：

| 节点 $u$ | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- |
| $\mathrm{subtree\_size}[u]$ | 4 | 3 | 2 | 1 |
| $\mathrm{dist\_sum}[u]$ | 6 | 4 | 4 | 6 |

先看 `subtree_size` 一行：叶子 $4$ 是 $1$，向上累加得到 $3$、$2$、$4$。再看 `dist_sum` 一行：`dist_sum[1] = 0+1+2+3 = 6`，然后 $\mathrm{dist\_sum}[2] = 6 + 4 - 2\times3 = 4$，$\mathrm{dist\_sum}[3] = 4 + 4 - 2\times2 = 4$，$\mathrm{dist\_sum}[4] = 4 + 4 - 2\times1 = 6$。节点 $2$ 与 $3$ 距离和同为 $4$，取编号小的 $2$，与样例输出 `2 4` 一致。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：BFS、求子树大小、换根 DP、扫描答案各 $O(n)$，总 $O(n)$。
- 空间：邻接表与四个 $O(n)$ 数组，总 $O(n)$。

## 总结

"树上所有点到某点距离和"这类问题，通用套路是先以任意点为根求出子树大小，再用换根公式 `dist_sum[v] = dist_sum[u] + n - 2 * subtree_size[v]` 沿树边递推。难点只在把"重新算一棵树"化简成"相邻两棵子树规模差驱动的增量转移"。距离和最小的点就是树的重心；rbook 的《[树的中心](https://rbook2.roj.ac.cn/graph/center_of_tree/index.html)》讲的是另一个目标（到所有点最大距离最小），注意不要混淆。

## 图示解析

这张 ASCII 图展示整道题的解题路线：

```text
朴素模拟（brute.cpp）
  枚举会议点 x，从 x 做一次 BFS 求距离和     每个点 O(n)
        |
        | 瓶颈：n 个点各 BFS 一次，O(n^2) 太大
        v
关键观察（换根公式）
  以 1 为根，dist_sum[1] = 所有点深度和
  v 是 u 的儿子时：
  dist_sum[v] = dist_sum[u] + n - 2 * subtree_size[v]
  （v 子树内距离 -1，其余点距离 +1）
        |
        v
换根 DP（main.cpp）
  BFS 求遍历序 / 父亲 / 深度 -> dist_sum[1]
  逆序遍历序累加 subtree_size
  正序遍历序按公式递推所有 dist_sum
  扫描取最小，相等保留编号小者
        |
        v
复杂度 O(n)，空间 O(n)
```

图中三条主线对应"暴力慢在哪里""相邻点距离和如何 $O(1)$ 转移""换根 DP 如何分三步完成"。核心是把 $O(n^2)$ 次"完整 BFS"替换为 $O(n)$ 次"跨一条边的增量转移"，代价只是额外统计一遍子树大小。
