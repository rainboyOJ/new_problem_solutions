---
oj: "roj"
problem_id: "1330"
title: "【例8.3】最少步数"
description: "从 (1,1) 反向 BFS 一次得到全图距离，两次查表回答两匹马的最少步数。"
difficulty: "普及-"
date: 2026-09-30 05:32
updated: 2026-10-06 02:35
toc: true
tags: ["BFS", "最短路", "网格", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1255"
    reason: "B 的正解把 A 教的「首次入队即最短步数、并用同一张表兼作访问标记」这套网格无权图 BFS 引擎与状态设计原样用在 100×100 棋盘上（代码里 dist 字典既存距离又判重），只是把源点从起点搬到终点 (1,1) 做一次反向预处理并叠加 12 种走法。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1330
---

## 题目描述

在 100×100 的棋盘上，一匹马既能走“日”字也能走“田”字。输入两个起点 A、B 的坐标，输出它们到左上角 (1,1) 的最少步数。

## 思路

12 种走法都成对取反，图是无向无权图，所以从 (1,1) 反向做一次 BFS 即可得到所有格子到 (1,1) 的最短距离；两个起点各查一次表即可。

## 参考代码

@include-code(./main.cpp, cpp)
