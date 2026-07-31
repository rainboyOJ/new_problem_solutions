---
oj: "shumeng"
problem_id: "CSP201512C"
title: "画图"
description: "按操作模拟水平线、竖直线与四连通填充，最后按纵坐标倒序输出画布。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "BFS", "二维数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512C
---

[[TOC]]

### 题意

在坐标原点位于左下角的 ASCII 画布上，依次执行画线和四连通填充操作。

### 思路

用 `board[y][x]` 保存画布。水平、竖直线逐格写入 `-`、`|`，遇到另一方向线段时改为 `+`。填充从起点 BFS，只能经过不是 `-`、`|`、`+` 的格子。坐标向上增长，输出时从最大 `y` 到 0。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每次填充最多访问整个画布，时间复杂度为 $O(qmn)$，空间复杂度为 $O(mn)$。

### 总结

绘制与填充严格按输入顺序执行；线段是填充的边界，先前填入的字母不是边界。
