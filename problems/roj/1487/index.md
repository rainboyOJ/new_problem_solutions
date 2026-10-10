---
oj: "roj"
problem_id: "1487"
title: "「一本通 3.1 例 2」北极通讯网络"
description: "将卫星设备等价于免费边连接连通块，利用 Kruskal 最小生成树消去最大边权求瓶颈距离"
difficulty: "普及"
date: 2026-09-30 14:14
updated: 2026-10-06 00:31
toc: true
tags:
  - 最小生成树
  - 贪心
  - 并查集
favorite: false
favorite_reason: ""
categories:
  - 图论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1487
---

[[TOC]]

## 题目描述

$n$ 座村庄坐标已知，任意两村可用距离不超过 $d$ 的无线电直接通讯，另有 $k$ 台卫星设备可配给任意村庄（卫星直连无距离限制）。求保证所有村庄连通的最小 $d$，保留两位小数。

## 思路

$k$ 台卫星设备等价于把村庄分成至多 $\max(k,1)$ 个连通块、块间用卫星免费互联，问题转化为求最小生成树后删去最大的 $\max(k-1,0)$ 条边，剩余最大边权即为答案；$k \ge n$ 时答案为 0。用 Kruskal 求出生成树各边权，升序取倒数第 $\max(k,1)$ 大即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
