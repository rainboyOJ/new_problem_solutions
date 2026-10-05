---
oj: "roj"
problem_id: "1582"
title: "「一本通 5.2 练习 3」周年纪念晚会"
description: "把人事关系看成一棵树，每个节点记录选与不选两种最优值，自底向上合并，O(N) 求最大欢乐度。"
difficulty: "普及-"
date: 2026-09-30 19:59
updated: 2026-10-06 00:48
toc: true
tags: ["树形DP", "动态规划", "树"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1582
---

[[TOC]]

## 题目描述

学校职员构成一棵以校长为根的人事关系树，编号 $1..N$，第 $i$ 人有欢乐度 $p_i$。要求选出一份名单，使任意一人与其直接上司不同时参加，求总欢乐度最大值。输入第一行为 $N$，随后 $N$ 行每行一个 $p_i$，接着每行 `L K` 表示 $K$ 是 $L$ 的直接上司、以 `0 0` 结束；输出最大欢乐度。样例输入 `7 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 3 / 2 3 / 6 4 / 7 4 / 4 5 / 3 5 / 0 0`，输出 `5`。数据范围 $1 \leqslant N \leqslant 6000$，$-128 \leqslant p_i \leqslant 127$。

## 思路

树形 DP：每个节点保留两个值，`dp0[u]` 为 $u$ 不参加时子树的最大欢乐度，`dp1[u]` 为 $u$ 参加时的值，转移为 `dp0[u]=Σmax(dp0[v],dp1[v])`、`dp1[u]=p[u]+Σdp0[v]`（$v$ 是 $u$ 的直接下属）。按后序（孩子先于父亲）合并，链深可达 6000，用迭代后序避免递归爆栈，答案为 `max(dp0[root], dp1[root])`。

## 参考代码

@include-code(./main.cpp, cpp)
