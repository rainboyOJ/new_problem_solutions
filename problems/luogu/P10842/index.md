---
oj: "luogu"
problem_id: "P10842"
title: "【MX-J2-T3】Piggy and Trees"
description: "f(u,v,i) 为 i 到 u-v 路径的距离，闭式化简化得答案 = D*(n-2)/2，D 用边贡献 size*(n-size) 累加。"
difficulty: "普及+/提高-"
date: 2026-08-14 15:01
toc: true
tags: ["树形结构", "计数", "组合计数", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P10842
---

[[TOC]]

## 形式化题目

给定一棵 $n$ 个结点的树。对点对 $(u, v)$ 与点 $i$，定义 $f(u,v,i)$：在满足 $dis(u,x)+dis(v,x)=dis(u,v)$ 的点 $x$ 中，$dis(x,i)$ 的最小值。求

$$\sum_{u < v} \sum_{i} f(u,v,i) \bmod (10^9+7)$$

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 按定义直接计算：对每对 $(u,v)$ 枚举所有点 $x$ 检查等式，得到候选集合，再对每个 $i$ 求集合中到 $x$ 的最小距离。三层枚举加距离查询是 $O(n^4)$，$n = 2 \times 10^5$ 完全不可行。

两步化简把问题变成一遍 DFS：

**第一步，看清 f 是什么**。树上三角不等式取等 $dis(u,x)+dis(v,x)=dis(u,v)$ 当且仅当 $x$ 在 $u$ 到 $v$ 的路径上。所以 $f(u,v,i)$ 就是点 $i$ 到路径 $u$-$v$ 的最小距离。设 $w$ 为 $i$ 到路径的垂足，则

$$f(u,v,i) = \frac{dis(i,u)+dis(i,v)-dis(u,v)}{2}$$

**第二步，交换求和次序**。记 $D = \sum_{u<v} dis(u,v)$ 为所有点对距离和。把闭式代入三层和式：

$$\sum_{u<v}\sum_i f(u,v,i) = \frac{1}{2}\left[(n-1)\sum_{i,j}dis(i,j) - nD\right] = \frac{D(n-2)}{2}$$

最后，$D$ 可以用**边贡献**线性求出：一条边把树分成大小为 $a$、$b$ 的两部分，恰好有 $a \times b$ 个点对穿过这条边，所以 $D = \sum_{\text{边}} a \times b$。一遍 DFS 求子树大小即可。

下面这张表展示样例 1（星形，中心 1 连 2,3,4）每条边的贡献：

| 边 | 一侧点数 | 另一侧点数 | 贡献 |
| --- | --- | --- | --- |
| (1,2) | 1 | 3 | 3 |
| (1,3) | 1 | 3 | 3 |
| (1,4) | 1 | 3 | 3 |

观察要点：每条边都连接中心与一个叶子，贡献都是 $1 \times 3 = 3$，总和 $D = 9$；代入公式 $9 \times (4-2)/2 = 9$，与样例答案一致。星形里任意两点的路径都经过中心，`f` 的求和直观上与距离和成比例。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：一遍 DFS 求子树大小并累计边贡献，$O(n)$。
- 空间：邻接表 $O(n)$。

## 总结

这道题的价值在**把三层求和整体化简**：先识别出 $f$ 的几何意义（点到路径的距离）并写成距离的闭式，再交换求和次序，把"每对点 × 每个点"的 $O(n^3)$ 结构坍缩成只依赖 $D$ 的公式；而 $D$ 又通过边贡献 $size \times (n-size)$ 一遍 DFS 求出。这类"点对路径相关求和"的题目，优先尝试：距离闭式 → 求和交换 → 边贡献，往往能直接降到 $O(n)$。

## 图示解析

这张 ASCII 图展示整道题的解题路线：

```text
题意：sum_{u<v} sum_i f(u,v,i)，f 是"满足距离等式的 x 中到 i 最近的距离"
        |
        | 暴力：O(n^4) 按定义枚举 x（brute.cpp）
        v
关键观察 1：dis(u,x)+dis(v,x)=dis(u,v) ⟺ x 在 u-v 路径上
   f(u,v,i) = 点 i 到路径 u-v 的最小距离
        |
        | 设垂足 w，代入三条距离关系
        v
关键观察 2：f = (dis(i,u)+dis(i,v)-dis(u,v))/2
        |
        | 交换求和次序
        v
化简：答案 = D*(n-2)/2，D = sum_{u<v} dis(u,v)
        |
        | 边贡献：每条边贡献 size*(n-size)
        v
实现：一遍 DFS 求子树大小，O(n)
   答案 = D * (n-2) * inv(2) mod MOD
```

图中主线是"识别几何意义 → 距离闭式 → 求和化简 → 边贡献"。真正要掌握的是：三层求和不要硬算，先找每一项的闭式，再整体交换求和次序。
