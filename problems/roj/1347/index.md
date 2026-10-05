---
oj: "roj"
problem_id: "1347"
title: "【例4-8】格子游戏"
description: "在 n×n 点阵上按顺序加边，加边后成圈等价于新边两端已经连通；连通只合并不分裂，用并查集增量维护，第一条两端同块的边就是答案。"
difficulty: "普及-"
date: 2026-09-30 06:22
updated: 2026-10-05 11:16
toc: true
tags: ["并查集", "图论", "环检测", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1347
---

[[TOC]]

## 题目描述

n×n 点阵上依次加入 m 条相邻点之间的无向边，'D' 表示向下，'R' 表示向右，边不重复。输入 n、m 与每条边起点 (x,y) 和方向；输出首次成圈的步数 i，若 m 条边加完仍无圈则输出 draw。样例输入 3 5 加 5 条边后输出 4。数据范围 n ≤ 200。

## 思路

加边后成圈等价于新边两端已经连通。边只增不减，连通性只合并不分裂，用并查集增量维护；按顺序处理每条边，若两端同根说明该步封圈，否则合并两块。

## 参考代码

@include-code(./main.cpp, cpp)
