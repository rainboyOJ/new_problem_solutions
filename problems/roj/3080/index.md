---
oj: "roj"
problem_id: "3080"
title: "武士风度的牛"
description: "BFS 求网格上马步最短路，首次到达草地即最少跳跃次数。"
difficulty: "普及-"
date: 2026-10-01 15:14
updated: 2026-10-06 02:35
toc: true
tags: ["搜索", "BFS", "最短路", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1747"
    reason: "A 教的无权图最短路 BFS 正是 B 的解法骨架：B 的 main.py 把非障碍格建成无权图后用队列逐层扩展、首次到达 H 即返回层数，只额外叠加障碍过滤、一维下标还原与提前退出，并未用上 A 特有的 12 种走法与反向 BFS，故属模板级复用。"
  - oj: "roj"
    problem_id: "1329"
    reason: "B 的网格 BFS 直接沿用 A 教的「入队即标记、标记兼作访问、每格至多入队一次」这一状态设计（main.py 里先写 dist[nxt] = dist[pos] + 1 再 append），只是把标记从原地抹 '0' 换成 dist 初值 -1，并叠加马的 8 种跳跃位移与首次够到 H 即最短距离这一判定。"
  - oj: "roj"
    problem_id: "1255"
    reason: "B 直接复用 A 的「首次到达即最短距离、标记与判重合一份」这一 BFS 核心步骤，只是换成马的 8 位移并把前驱标记换成 dist 数组"
common: []
recommend: []
source: https://roj.ac.cn/problem/3080
---

[[TOC]]

## 题目描述

给定 $C \times R$ 网格（$C,R \leqslant 150$），格子为 `.`、`*`、`K`、`H`。棋子从 `K` 出发按马走日跳跃，落点需在网格内且非障碍，求到 `H` 的最少跳跃次数。数据保证有解。

**输入**：$C\ R$，随后 $R$ 行地图。  
**输出**：最少跳跃次数。

## 思路

把非障碍格看成顶点、马步看成边权为 1 的边，得到无权无向图。BFS 按层扩展，dist 数组兼作判重，首次到达 `H` 时的层数就是答案。

## 参考代码

@include-code(./main.cpp, cpp)
