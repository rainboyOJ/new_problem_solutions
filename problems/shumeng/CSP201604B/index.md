---
oj: "shumeng"
problem_id: "CSP201604B"
title: "俄罗斯方块"
description: "保留方块图案的四列定位，逐行试探下落到首次碰撞前的位置。"
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
source: https://oj.shumeng.tech/p/CSP201604B
---

[[TOC]]

### 题意

给定棋盘、4×4 方块图案及起始列，模拟方块竖直下落后的棋盘。

### 思路

图案左边界对应给定列，即使左侧列全为 0 也不能裁去。将图案从最上方开始，每次判断下移一行后所有实心格是否仍在棋盘内且不与已有方块重叠；不能下移时，将当前图案写入棋盘。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

棋盘高固定为 15，时间复杂度为 $O(15\times16)$，空间复杂度为 $O(1)$。

### 总结

下落判断只检查图案中值为 1 的格子。题目不要求消行，落定后直接输出即可。
