---
oj: "luogu"
problem_id: "P4017"
title: "最大食物链计数"
description: "从所有入度为零的生产者开始拓扑 DP，把路径条数沿捕食边累加到出度为零的消费者。"
difficulty: "普及/提高-"
date: 2026-07-16 18:42
toc: true
tags: ["DAG", "拓扑排序", "动态规划", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4017
---

[[TOC]]

### 题意

在无环食物网中，边 `A -> B` 表示 `B` 吃 `A`。统计从不捕食其他生物的生产者到不被其他生物捕食的消费者的路径数量，答案模 `80112002`。

### 思路

生产者是入度为 `0` 的点，消费者是出度为 `0` 的点。令 `ways[v]` 表示从任意生产者走到 `v` 的食物链条数：

- 每个生产者初始化 `ways=1`；
- 拓扑处理中遇到边 `u -> v`，执行 `ways[v]+=ways[u]`；
- 最后把所有消费者的 `ways` 相加。

样例的状态变化如下，表中“新增来源”说明本轮由哪条边贡献：

| 处理点 | 新增来源 | 处理后的关键状态 |
| --- | --- | --- |
| `1` | 生产者初值 | `ways[2]=1, ways[3]=1` |
| `2` | `1 -> 2` | `ways[3]=2, ways[5]=1` |
| `3` | 两条到 `3` 的路径 | `ways[4]=2, ways[5]=3` |
| `4` | 两条到 `4` 的路径 | `ways[5]=5` |

唯一消费者 `5` 最终得到 `5` 条链。

### Python 知识

- `deque` 支持 $O(1)$ 的 `popleft`，适合 Kahn 拓扑队列。
- `deque(node for ... if ...)` 用生成器直接初始化所有零入度点。
- `sum(ways[node] for ... if not graph[node])` 只汇总出度为零的消费者。
- 每次转移立即取模，防止路径数大幅增长。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 队列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：条件生成器与 `sum`。

### 代码

@include-code(./main.py, python)

### 复杂度

每个点和每条边处理一次，时间复杂度 $O(n+m)$，空间复杂度 $O(n+m)$。

### 总结

DAG 路径计数的核心是让拓扑序保证“前驱贡献全部到齐后再处理当前点”。起点初始化为一，沿边累加，终点汇总即可。
