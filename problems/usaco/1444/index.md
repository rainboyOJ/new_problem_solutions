---
oj: "usaco"
problem_id: "1444"
title: "Farmer John's Cheese Block"
description: "固定两维维护每条直线还剩多少奶酪块，某条线第一次清空时答案加一。"
difficulty: "普及-"
date: 2026-07-11 15:31
toc: true
tags: ["统计", "模拟", "思维", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1444
---

[[TOC]]

### 题意

有一个 $N\times N\times N$ 的奶酪立方体。每次会切掉一个坐标为 `(x,y,z)` 的 $1\times 1\times 1$ 小方块。

每次切割后，问有多少种方式可以放入一个 $1\times 1\times N$ 的长砖块，使它不与剩余奶酪重叠。

砖块可以沿 x、y、z 三个方向摆放。

### 思路

先看一个直接重算的朴素写法：

@include-code(./brute.cpp, cpp)

这个暴力每次切割后，检查三种方向的所有直线是否已经完全切空。它直观但太慢。

一个 $1\times 1\times N$ 的砖块一定对应一条长度为 $N$ 的整线：

- 固定 `y,z`，沿 x 方向。
- 固定 `x,z`，沿 y 方向。
- 固定 `x,y`，沿 z 方向。

切掉一个小方块 `(x,y,z)`，只会影响穿过它的三条线：

```text
固定 y,z 的 x 方向线
固定 x,z 的 y 方向线
固定 x,y 的 z 方向线
```

所以我们维护每条线还剩多少奶酪块。

初始每条线都剩 `N` 块。每次切掉 `(x,y,z)`：

- `left_yz[y][z]--`
- `left_xz[x][z]--`
- `left_xy[x][y]--`

如果某个值第一次变成 0，就说明这条线已经被完全切空，可以新增一种放砖块方案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

初始化三个二维数组需要 $O(N^2)$。

每次更新只修改三条线，所以总时间复杂度为 $O(N^2+Q)$。

空间复杂度为 $O(N^2)$。

### 总结

本题的关键是把三维问题降成“固定两维的一条线”。

一次切割只影响三条线，增量维护剩余数量即可。
