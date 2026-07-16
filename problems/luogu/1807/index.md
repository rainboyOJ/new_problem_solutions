---
oj: "luogu"
problem_id: "P1807"
title: "最长路"
description: "利用每条边都从小编号指向大编号的天然拓扑序，按编号进行 DAG 最长路 DP。"
difficulty: "普及/提高-"
date: 2026-06-19 22:41
toc: true
tags: ["DAG", "拓扑序", "动态规划", "图论", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1807
---

[[TOC]]

### 题意

给出带权有向无环图，求点 `1` 到点 `n` 的最长路径；不可达输出 `-1`。题目保证每条边 `u -> v` 都满足 `u<v`，边权可能为负。

### 思路

令 `distance[v]` 表示从 `1` 到 `v` 的最长路。若 `u` 可达，对边 `u -> v` 尝试：

$$distance[v]=\max(distance[v],distance[u]+w)$$

因为所有边都从小编号指向大编号，`1,2,...,n` 本身就是拓扑序，不需要计算入度。处理 `u` 时，所有可能到达 `u` 的前驱都已经处理完。

下表展示一个小图的转移：`1->2(3)`、`1->3(2)`、`2->4(4)`、`3->4(10)`。

| 处理点 | 转移来源 | 更新结果 |
| --- | --- | --- |
| `1` | `distance[1]=0` | `distance[2]=3, distance[3]=2` |
| `2` | `3+4` | `distance[4]=7` |
| `3` | `2+10` | `distance[4]=12` |
| `4` | 所有前驱已处理 | 最终最长路为 `12` |

不可达状态用 `None` 表示。不能初始化成 `0`，因为合法最长路可能是负数。

### Python 知识

- `None` 清楚地区分“不可达”和合法的负数、零距离。
- 邻接表中用 `(neighbor,weight)` 元组保存带权边，循环时直接解包。
- `range(1,n+1)` 就是题目保证的天然拓扑序。
- 条件表达式 `-1 if ... else ...` 简洁处理最终不可达输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：列表与元组邻接表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：哨兵值和负权边注意点。

### 代码

@include-code(./main.py, python)

### 复杂度

每个点、每条边处理一次，时间复杂度 $O(n+m)$，空间复杂度 $O(n+m)$。

### 总结

DAG 最长路依赖拓扑顺序。本题的编号顺序已经满足拓扑要求，直接按编号松弛即可；负权存在时必须正确表示不可达状态。

### 一图流解析

这张图把原题已有的建模和转移内容压缩到一页，保留作为复盘材料。

![一图流解析](./one-page-explainer.png)
