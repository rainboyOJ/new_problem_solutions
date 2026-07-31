---
oj: "shumeng"
problem_id: "CSP201512B"
title: "消除类游戏"
description: "在原棋盘上分别标记横竖连续三个以上的同色段，再同时清除。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "二维数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512B
---

[[TOC]]

### 题意

对棋盘执行一次消除：横向或纵向连续至少三个同色棋子都变为 0，多个位置同时生效。

### 思路

扫描每一行和每一列的极长相同段，长度至少为 3 时在 `removed` 数组中标记。标记完成后才输出结果，避免先删除一处而影响另一处判断。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(nm)$，空间复杂度为 $O(nm)$。

### 总结

“同时消除”要求检测与修改分离。一个格子可被横向、纵向任一方向标记，最终统一置零。
