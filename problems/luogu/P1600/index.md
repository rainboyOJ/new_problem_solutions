---
oj: "luogu"
problem_id: "P1600"
title: "[NOIP 2016 提高组] 天天爱跑步"
description: "把观察条件改写为深度等式，按 LCA 拆两段路径，用桶与树上差分在 DFS 中统计每个观察员看到的人数。"
difficulty: "省选/NOI-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "树形差分", "事件计数", "桶", "倍增"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1600
---

[[TOC]]

## 形式化题目

有一棵 $n$ 个点的树，根为 $1$。$m$ 个玩家同时从第 $0$ 秒出发，玩家 $i$ 从 $s_i$ 沿唯一最短路径以每秒一条边的速度走向 $t_i$，到达终点立即消失。每个点 $u$ 有一个观察时刻 $w_u$，观察员只在第 $w_u$ 秒看一次：玩家恰在这一秒位于 $u$ 点（若 $u$ 是终点则为"恰好在这一秒到达"）就被看到。

对每个点 $u$，求能被看到的玩家数量。

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 对每个玩家先 DFS 搜出唯一路径，再逐秒走过路径逐时刻打点，最后对每个观察员统计"到达时刻恰好等于 $w_u$"的玩家数。单个玩家 $O(n)$，总复杂度 $O(nm)$，$3 \times 10^5$ 的数据完全不可行。

**关键观察：把到达时刻写成深度等式，路径问题就退化成"特征值匹配"。** 设 $p = \mathrm{lca}(s,t)$，玩家第 $0$ 秒从 $s$ 出发，到达某点的时间就是"从 $s$ 走到该点的边数"。按 $p$ 把路径拆成两段：

- **上行段 $s \to p$**：点 $u$ 的到达时刻是 $depth[s] - depth[u]$，观察员看到它当且仅当

$$depth[s] - depth[u] = w_u \iff depth[s] = depth[u] + w_u$$

- **下行段 $p \to t$（不含 $p$）**：点 $u$ 的到达时刻是 $depth[s] - 2 \cdot depth[p] + depth[u]$，观察员看到它当且仅当

$$depth[s] - 2 \cdot depth[p] + depth[u] = w_u \iff depth[s] - 2 \cdot depth[p] = w_u - depth[u]$$

两个等式左边都**只与路径有关**（路径特征值：$depth[s]$ 与 $depth[s] - 2 \cdot depth[p]$），右边**只与观察点有关**（$depth[u] + w_u$ 与 $w_u - depth[u]$）。于是"谁看到谁"变成"路径特征值是否等于点的固定 key"。

**最终做法：树上差分 + 桶 + 一次 DFS 汇总。**

1. 对每条路径求 $p = \mathrm{lca}(s,t)$，挂四个事件：

   | 段 | 特征值 key | 挂点 |
   | --- | --- | --- |
   | 上行 $s \to p$ | $depth[s]$ | $s: +1$，$parent(p): -1$（$p \ne 1$ 时） |
   | 下行 $p \to t$ | $depth[s] - 2 \cdot depth[p] + offset$ | $t: +1$，$p: -1$ |

   $+1$ 与 $-1$ 保证该特征值只对路径覆盖的那一段祖先链生效（树上差分的标准写法）。
2. 显式栈做后序 DFS：进入点 $u$ 的子树前，记下两个桶中"目标 key"（$depth[u] + w_u$ 与 $w_u - depth[u] + offset$）的读数；处理完整棵子树（把 $u$ 子树内所有事件加入桶）后再读一次。两次读数之差就是只来自 $u$ 子树的命中数，相加即 $answer[u]$。

以样例 1 逐玩家推演（树：$2-3,1-2,1-4,4-5,4-6$，$w = (0,2,5,1,2,3)$）：

| 玩家 | 路径 | 各点到达时刻 | 命中（时刻 = w） |
| --- | --- | --- | --- |
| $1 \to 5$ | 1-4-5 | 1:0, 4:1, 5:2 | 点 1（0=0）、点 4（1=1）、点 5（2=2） |
| $1 \to 3$ | 1-2-3 | 1:0, 2:1, 3:2 | 点 1（0=0） |
| $2 \to 6$ | 2-1-4-6 | 2:0, 1:1, 4:2, 6:3 | 点 6（3=3） |

每列点数正好是答案 $2\ 0\ 0\ 1\ 1\ 1$，与样例输出一致。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：预处理 $O(n \log n)$，每个玩家一次 $lca$ $O(m \log n)$，汇总 DFS $O(n + m)$，总 $O((n+m)\log n)$。
- 空间：倍增表 $O(n \log n)$，邻接表与事件表 $O(n + m)$，桶 $O(n)$。

## 总结

"天天爱跑步"是树上差分的进阶题：路径覆盖之外还叠加了"时刻匹配"这一维度。套路是把到达时刻写成深度等式，让路径的贡献退化成两个只与路径有关的特征值，再用 $+1/-1$ 事件 + 桶计数离线汇总。关键公式是上行段的 $depth[s] = depth[u] + w_u$ 与下行段的 $depth[s] - 2 \cdot depth[p] = w_u - depth[u]$：左边是路径特征值，右边是点的 key，相等即命中。实现上利用倍增 LCA 拆路径、显式栈避免深递归，是 $O((n+m)\log n)$ 的满分做法。rbook 的《[倍增求 LCA](https://rbook2.roj.ac.cn/tree-algo/jump-lca/index.html)》讲解了本解使用的 `lca-binary-lifting` 倍增 LCA 模板：先让深的点提到同一层，再从大到小一起跳。

## 图示解析

这张 ASCII 图展示整道题的解题路线：

```text
朴素模拟（brute.cpp）
  逐玩家 DFS 搜出 s -> t 路径，逐秒打点记录到达时刻   O(nm)
        |
        | 瓶颈：每个玩家扫描整条路径，路径重叠被反复走
        v
关键观察（差分转换）
  上行段 s -> lca:   到达时刻 = depth[s] - depth[u]
                     命中条件: depth[s] = depth[u] + w[u]
  下行段 lca -> t:   到达时刻 = depth[s] - 2*depth[lca] + depth[u]
                     命中条件: depth[s] - 2*depth[lca] = w[u] - depth[u]
  左边是路径特征值，右边是点的 key，相等即命中
        |
        v
树上差分 + 桶 + 后序 DFS（main.cpp）
  上行: s +1, parent(lca) -1   特征值 depth[s]
  下行: t +1, lca -1           特征值 depth[s] - 2*depth[lca] + offset
  显式栈后序遍历：进入子树前记桶值，子树处理完再读，
  差值 = 该点子树内命中的玩家数 = answer[u]
        |
        v
复杂度 O((n + m) log n)，空间 O(n log n + m)
```

图中三条主线对应"暴力慢在哪""路径贡献如何被压缩成两个深度等式""桶 + 树上差分如何把命中匹配批量完成"。核心是：时刻匹配维度被吸收进深度等式后，"观察员看到谁"就只剩特征值相等一个判断，配合 $+1/-1$ 事件即可一次 DFS 统计所有点。
