---
oj: "luogu"
problem_id: "P9724"
title: "[EC Final 2022] Chase Game"
description: "把追逃过程按第一次传送拆成两段：传送前 Pang 固定在 k，是一次带权最短路；传送后在某点 v 沿 v→n 的最短路走，伤害成周期为 d 的等差数列，用公式 O(1) 结算。"
difficulty: "提高"
date: 2026-10-02 15:23
updated: 2026-10-07 12:15
toc: true
tags: ["图论", "最短路", "BFS", "Dijkstra", "等差数列", "贪心"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1382"
    reason: "B 正解的第一步就是在每步伤害 d-dist(k,v) 构成的非负权图上复用 A 教的堆优化 Dijkstra（main.cpp 同样是 priority_queue + vis 惰性删除的定型模板）求出 dist_shou，再在其外叠加「以第一次传送分两段、等差数列 O(1) 结算」的额外流程。"
  - oj: "luogu"
    problem_id: "P4779"
    reason: "B 的正解第一段把 A 教的堆优化 Dijkstra 松弛出边原样复用，只是把边权换成 d-dist_k[v] 并在松弛时按 dist_k[v] 分流出首次传送判定"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P9724
---

[[TOC]]

## 形式化题目

给定一张 $n$ 个点、$m$ 条边的无向无权连通图。Shou 从 $1$ 出发，目标是走到 $n$；Pang 初始在 $k$，攻击范围为 $d$。

过程按“秒”推进，每一秒：

1. Shou 先选择一个相邻顶点并走过去；
2. **到达之后**才结算伤害。设此刻 Shou 在 $v$、Pang 在 $p$，$dis = \mathrm{dist}(p, v)$ 为图上最短路长度：
   - $dis < d$：Pang 留在 $p$，Shou 受到 $d - dis$ 点伤害；
   - $dis \geqslant d$：Pang 传送到 $v$，Shou 受到 $d$ 点伤害。

到达 $n$ 的那一次攻击也要计入。求 Shou 从 $1$ 走到 $n$ 所能承受的最小总伤害。

## 暴力解法

### 思路

题目把两个对象的位置都摆在了明面上，最忠实的建模就是把它们都放进状态：

> 状态 $(p, u)$ 表示 Pang 在 $p$、Shou 在 $u$，初始状态为 $(k, 1)$。

对 Shou 从 $u$ 走向的每条边 $u \!-\! v$，有一条转移（判定用的是**移动之后**的 $v$）：

- 若 $\mathrm{dist}(p, v) < d$：迁移到 $(p, v)$，花费 $d - \mathrm{dist}(p, v)$；
- 否则：Pang 传送到 $v$，迁移到 $(v, v)$，花费 $d$。

所有边权都非负，于是在 $n^2$ 个状态上做一次堆优化 Dijkstra，最终在所有的 $(p, n)$ 中取最小值即可。

以样例 1（$n=5$，$k=3$，$d=1$）为例，路径 $1 \to 3 \to 5$ 的状态变化是：

| 步 | Shou 移动 | 到达后状态 $(p,u)$ | $\mathrm{dist}(p,u)$ | 本步伤害 |
| --- | --- | --- | --- | --- |
| 1 | $1 \to 3$ | $(3,3)$ | $0 < 1$ | $d-0=1$（Pang 不动） |
| 2 | $3 \to 5$ | $(3,5)$ | $1 \geqslant 1$ | $d=1$（Pang 传送到 5） |

总伤害 $2$，与样例一致。这个建模完全照抄规则，因此一定正确。

### 代码

@include-code(./brute.cpp, cpp)

### 复杂度

状态数 $O(n^2)$，转移数 $O(nm)$，堆优化 Dijkstra 的时间复杂度 $O(nm + n^2\log n)$，空间复杂度 $O(n^2)$。只适合 $n \leqslant 64$ 的小数据。

### 瓶颈

瓶颈是**显式枚举 Pang 的位置**：$n = 10^5$ 时状态数就爆了。

但回顾规则会发现，Pang 的位置其实没有多少自由度：他要么还没有动过，仍在 $k$；要么已经传送，停在 Shou 上一次被追上的那个点。也就是说，Pang 的位置是被 Shou 的轨迹决定的，没有必要求解它。

## 正解

### 思路

以**第一次传送**为分界线，把过程切成两段。

**第一段：还没有发生传送。** 只要每次判定都满足 $dis < d$，Pang 就一直待在 $k$。于是这是无数值自由度的一张固定权图：从 $u$ 走向邻居 $v$ 的伤害只取决于 $v$，为 $d - \mathrm{dist}(k, v)$。以 $1$ 为源跑一次带权最短路，记 `dist_shou[u]`。

**第二段：第一次传送之后。** 设传送发生在点 $v$（Shou 某一步后到达 $v$，且 $\mathrm{dist}(k, v) \geqslant d$）。此刻 Pang 与 Shou 都在 $v$。之后 Shou 每走一步，与 Pang 的距离最多 $+1$；沿 $v \to n$ 的**最短路**走则每步恰好 $+1$，伤害依次是
$$d-1,\ d-2,\ \ldots,\ 1,$$
当距离重新达到 $d$ 时 Pang 再次传送、又打出 $d$ 点伤害。于是伤害序列以 $d$ 为周期循环：

$$d,\ d-1,\ d-2,\ \ldots,\ 1,\ d,\ d-1,\ \ldots$$

从 $v$ 到 $n$ 共 $\mathrm{dist}(v, n)$ 步，加上触发传送的那一步，一共 $x = \mathrm{dist}(v, n) + 1$ 项。设 $x = qd + r$，则

$$\text{teleport\_cost}(x) = q \cdot \frac{d(d+1)}{2} + \frac{(d-r+1+d)\cdot r}{2}.$$

这一步只和 $\mathrm{dist}(v, n)$ 有关，可以 $O(1)$ 结算，不需要再搜索。

于是正解只需：

1. 以 $k$ 为源 BFS，得 `dist_k[v] = dist(k, v)`；
2. 以 $n$ 为源 BFS，得 `dist_n[v] = dist(v, n)`；
3. 在“Pang 仍在 $k$”的阶段跑带权 Dijkstra，遍历邻居 $v$ 时：
   - `dist_k[v] >= d`：$v$ 可以作为首次传送点，用 `dist_shou[u] + teleport_cost(dist_n[v] + 1)` 更新答案；
   - 否则用 `dist_shou[u] + (d - dist_k[v])` 松弛 `dist_shou[v]`。

最后答案取 `min(ans, dist_shou[n])`，后者覆盖一次传送都没发生的情况。

下面用样例 1（$k=3$，$d=1$）看一下两段如何衔接。注意 $d=1$ 时只有 $v=k=3$ 满足 $\mathrm{dist}(k,v)<d$，所以第一段里只有 $3$ 能被松弛（`dist_shou[3] = 1`），其余邻居一律按“传送”立即结算：

| 从 $u$ | 到 $v$ | $\mathrm{dist}(k,v)$ | 处理方式 | 候选答案 |
| --- | --- | --- | --- | --- |
| 1 | 2 | 2 | 传送 | $0 + \text{cost}(\mathrm{dist}(2,5)+1)=0+3=3$ |
| 1 | 3 | 0 | 松弛 `dist_shou[3] = 0+(1-0) = 1` | — |
| 3 | 1 | 1 | 传送 | $1 + \text{cost}(3) = 4$ |
| 3 | 5 | 1 | 传送 | $1 + \text{cost}(1) = 2$ |

最小值 $2$ 来自 $u=3 \to v=5$：先在第一段“Pang 停在 3”时走到 3 消耗 $1$，再一步冲进终点触发传送消耗 $d=1$，合计 $2$，与样例一致。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

两次 BFS 为 $O(n+m)$，带权最短路为 $O((n+m)\log n)$，枚举首次传送点在遍历边时顺带完成。总时间复杂度 $O((n+m)\log n)$，空间复杂度 $O(n+m)$。

## 总结

本题的关键不是某个数据结构，而是**看出 Pang 的位置没有独立自由度**：

- 没传送时他固定在 $k$，第一段退化为一张固定权图上的最短路；
- 传送发生后他直接跳到 Shou 脚下，第二段的最优策略是沿最短路冲向 $n$，伤害由周期为 $d$ 的等差数列完全确定。

把“第一次传送”作为唯一的分界点枚举，就把 $n^2$ 的状态空间压缩回 $O(n+m)$。实现上有两个容易踩的坑：判定距离必须用**移动之后**的顶点，以及第二段步数要**加上触发传送的那一步**。
