---
oj: "roj"
problem_id: "1380"
title: "分糖果"
description: "糖果在无权图上每秒传一格，从 C 出发 BFS 求出到每个小朋友的最短时间，答案 = max(dist) + m + 1。"
difficulty: "普及-"
date: 2026-09-30 07:55
updated: 2026-10-05 12:30
toc: true
tags: ["图论", "bfs", "最短路", "python"]
favorite: false
favorite_reason: ""
categories: ["图论"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1380
---

[[TOC]]

## 题目描述

$n$ 个小朋友、$p$ 条"彼此身旁"关系构成无权无向图。糖果第一秒从 $c$ 号出发，每秒沿一条边传给身旁还没糖的人；每人从拿到糖起再吃 $m$ 秒（边吃边发，不影响传播）。求全部吃完的时刻。输入第一行 $n, p, c$，第二行 $m$，接下来 $p$ 行每行一对身旁关系；输出一个数即答案。样例：输入 `4 3 1 / 2 / 1 2 / 2 3 / 1 4` 输出 `5`。数据范围：$1 \leqslant n \leqslant 100000$，$m \leqslant n(n-1)/2$。

## 思路

吃糖不影响传播：第 $v$ 个人在 $\text{dist}(v)+1$ 秒收到糖，再吃 $m$ 秒吃完。无权图单源最短路用 BFS 求，最后吃完的一定是离 $c$ 最远的人，故答案为 $\max(\text{dist}) + m + 1$。

## 参考代码

@include-code(./main.cpp, cpp)
