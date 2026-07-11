---
oj: "usaco"
problem_id: "1420"
title: "Walking Along a Fence"
description: "把围栏按顺序逐格标成环形路径位置，查询时取两点标号差和补弧长的较小值。"
difficulty: "普及-"
date: 2026-07-11 15:44
toc: true
tags: ["模拟", "图形", "前缀和", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1420
---

[[TOC]]

### 题意

给定一个由水平、竖直线段组成的闭合围栏。每头奶牛给出围栏上的起点和终点。

因为围栏是一个环，从起点到终点有两条路，求较短的一条距离。

### 思路

先看一个更直观的路径展开写法：

@include-code(./brute.cpp, cpp)

这个写法把围栏上的整数点按行走顺序保存下来。正式代码可以直接用二维数组记录每个点的编号。

把围栏看成一条环形路径。我们从第一根柱子开始，按输入顺序沿围栏走一圈，给每个经过的整数点打标号：

```text
label[x][y] = 沿围栏走到 (x,y) 时已经走过的距离
```

同时得到围栏总长度 `perimeter`。

对一个查询，设两个点的标号分别为 `p1` 和 `p2`。沿一个方向走的距离是：

```text
d = abs(p1 - p2)
```

另一条路绕环走剩下部分，长度是：

```text
perimeter - d
```

答案就是：

```text
min(d, perimeter - d)
```

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

坐标范围上限为 $1000$，预处理沿围栏逐格行走，复杂度可视为 $O(1000^2)$。

每个查询 $O(1)$。

空间复杂度为 $O(1000^2)$。

### 总结

环上两点的最短距离，等于一段弧长和补弧长的较小值。

本题先把几何围栏转成一维环形路径编号，查询就变成了常数时间计算。
