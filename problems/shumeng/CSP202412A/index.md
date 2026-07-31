---
oj: "shumeng"
problem_id: "CSP202412A"
title: "移动"
description: "逐字符模拟机器人移动，并在每一步只接受仍处于正方形场地内的新位置。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202412A
---

[[TOC]]

### 题意

机器人位于 $n\times n$ 的方格场地中，`f`、`b`、`l`、`r` 分别表示向上、向下、向左、向右移动一格。若目标位置越出边界，则本次指令无效，位置保持不变。对每个起点和指令串输出最终位置。

### 思路

直接按指令串从左到右模拟。先根据当前指令计算候选位置，再判断两个坐标是否都在 $[1,n]$ 内；合法时更新位置，越界时忽略这条指令。

本题只需遍历每个指令一次，简单模拟即可。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有指令总长度为 $L$，时间复杂度为 $O(L)$，额外空间复杂度为 $O(1)$。

### 总结

边界判断必须在每一步移动后进行，不能只检查整串指令执行结束时的位置。
