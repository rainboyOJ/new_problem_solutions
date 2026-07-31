---
oj: "shumeng"
problem_id: "CSP201604D"
title: "游戏"
description: "危险结束前在时间扩展网格 BFS，时刻 101 后转为多源普通 BFS。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["BFS", "最短路", "网格图"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201604D
---

[[TOC]]

### 题意

在随时间变化的危险网格中，每个时刻必须移动一格，求到达右下角的最短时间。

### 思路

状态 `(row,column,time)` 表示恰在该时刻到达该格。BFS 扩展时检查下一时刻目标格是否危险。所有危险时段不超过 100，因此只展开到时刻 101；此时后所有格子安全，将时刻 101 的可达格作为多源 BFS 起点，普通最短路补完剩余距离。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(101nm)$，空间复杂度为 $O(101nm)$。

### 总结

危险判断使用到达时刻而不是离开时刻。超过所有危险结束时刻后，时间维度可以安全消去。
