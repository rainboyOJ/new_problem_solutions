---
oj: "roj"
problem_id: "2051"
title: "香甜的黄油"
description: "枚举每个牧场作为放糖点，从该点跑一次堆优化 Dijkstra，利用无向图最短路的对称性直接得到所有牛的路程和，取最小值。"
difficulty: "普及"
date: 2026-10-01 05:06
updated: 2026-10-06 10:28
toc: true
tags: ["图论", "最短路", "dijkstra", "枚举"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2051
---

[[TOC]]

## 题目描述

给定 $P$ 个牧场、$C$ 条无向正权道路，以及 $N$ 头牛各自所在的牧场。选一个牧场放糖，使所有牛到该牧场的最短路之和最小，输出这个最小值。$P \le 800$，$C \le 1450$。

## 思路

无向图最短路对称，从放糖点跑单源 Dijkstra 即可得到所有牛到它的距离。枚举每个牧场作为放糖点，取所有牛路程和的最小值。同一牧场多头牛用计数加权。

## 参考代码

@include-code(./main.cpp, cpp)
