---
oj: "roj"
problem_id: "1346"
title: "【例4-7】亲戚(relation)"
description: "把亲戚关系看成无向图的连通性，用带路径压缩与按大小合并的并查集合并全部关系，之后每次询问只比较两人的代表元。"
difficulty: "普及-"
date: 2026-09-30 06:22
updated: 2026-10-05 11:15
toc: true
tags: ["并查集", "连通性", "模板题", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1346
---

[[TOC]]

## 题目描述

给出 $N$ 个人（编号 $1 \sim N$）与 $M$ 条已知亲戚关系（亲戚关系可以传递），再给 $Q$ 次询问，每次问两人是否是亲戚。
输入：第一行 $N, M$；接下来 $M$ 行每行 $a_i, b_i$ 表示 $a_i$ 和 $b_i$ 是亲戚；然后一行 $Q$，接下来 $Q$ 行每行 $c_i, d_i$ 表示一次询问，$1 \le N \le 20000$，$1 \le M, Q \le 10^6$。输出：对每个询问输出一行，是亲戚输出 `Yes`，否则输出 `No`。
样例：输入 `10 7 / 2 4 / 5 7 / 1 3 / 8 9 / 1 2 / 5 6 / 2 3 / 3 / 3 4 / 7 10 / 8 9`（`/` 表示换行），输出 `Yes / No / Yes`。

## 思路

「是亲戚」具有传递性，本题就是无向图连通性问题：把每条关系看成一条边，用按大小合并加路径压缩的并查集把全部关系合并完，之后每次询问只需比较两人的代表元是否相同。

## 参考代码

@include-code(./main.cpp, cpp)
