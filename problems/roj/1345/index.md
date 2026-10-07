---
oj: "roj"
problem_id: "1345"
title: "【例4-6】香甜的黄油"
description: "枚举糖所在牧场，每个候选跑一次堆优化 Dijkstra，再按各牧场牛数加权求和取最小值；稀疏图 O(P(C+P)logP)，比 Floyd 的 O(P^3) 低一个数量级。"
difficulty: "普及-"
date: 2026-09-30 06:22
updated: 2026-10-05 10:46
toc: true
tags: ["图论", "最短路", "Dijkstra", "堆优化", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1345
---

[[TOC]]

## 题目描述

农夫 John 要把糖放在某个牧场上，让所有奶牛从各自所在牧场沿最短路走过来。P（2≤P≤800）个牧场之间有 C（1≤C≤1450）条双向道路（长度 1≤D≤255），N（1≤N≤500）头奶牛分别站在某些牧场（一个牧场可以有多头牛）。选一个牧场放糖，使所有奶牛走到它的最短路程之和最小，输出这个最小值。输入第一行 `N P C`，接下来 N 行每行一头牛所在的牧场号，再接下来 C 行每行 `A B D`。
样例输入 `3 4 5` / `2` / `3` / `4` / `1 2 1` / `1 3 5` / `2 3 7` / `2 4 3` / `3 4 5`，样例输出 `8`（放在 4 号牧场最优）。

## 思路

枚举糖放在哪个牧场，对每个候选跑一次堆优化 Dijkstra，再按每个牧场上的牛数加权求和取最小值。边权都为正、图很稀疏，单次 Dijkstra 复杂度 $O((C+P)\log P)$，总复杂度 $O(P(C+P)\log P)$；如果某个候选牧场到有牛的牧场不可达，直接跳过它。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
