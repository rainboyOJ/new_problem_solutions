---
oj: "roj"
problem_id: "1352"
title: "【例4-13】奖金"
description: "把奖金更高的意见反向建边得到 DAG，用 Kahn 拓扑排序按前驱最大值递推每人最小奖金，成环则输出 Poor Xed"
difficulty: "普及-"
date: 2026-09-30 06:35
updated: 2026-10-07 12:15
toc: true
tags: ["拓扑排序", "图论", "DAG", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1351"
    reason: "B 直接复用 A 教的 Kahn 入度归零入队循环（出队遍历后继、入度减 1、归零入队），只是把出队顺序换成 max(pay[u])+1 的定薪递推，并用出队计数补上判环。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1352
---

[[TOC]]

## 题目描述

公司要给 n 个员工发奖金，每人每张至少 100 元。m 条意见形如 "a 应该比 b 高"，即 $pay[a] \geqslant pay[b] + 1$。求满足所有意见的总奖金最小值；若约束互相矛盾，输出 `Poor Xed`。n≤10000，m≤20000。

输入：第一行 n m；之后 m 行每行 a b。输出：最少总奖金或 `Poor Xed`。

样例：`2 1\n1 2` → `201`（pay[2]=100，pay[1]=101）。

## 思路

把"a 高于 b"建成反向边 b→a，沿这条方向 Kahn 拓扑排序：入度归零的人直接取 100 元，出队时把后继 v 抬到 $\max(pay[v], pay[u]+1)$；最后若出队人数 < n 说明有环，输出 `Poor Xed`，否则累加 pay 即为最小总奖金。

## 参考代码

@include-code(./main.cpp, cpp)