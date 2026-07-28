---
oj: "leetcodecn"
problem_id: "spiral-matrix"
title: "螺旋矩阵"
description: "维护 top/bottom/left/right 四条边，按右/下/左/上收缩并检查边界，避免单行/单列重复。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "矩阵", "模拟", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/spiral-matrix/
---

[[TOC]]

### 题意

按顺时针螺旋顺序返回 m×n 矩阵中的所有元素。

### 思路

维护四条边界 top、bottom、left、right，每次按右、下、左、上四个方向遍历，遍历后收缩对应边界。关键是要在左和上方向前检查边界是否仍然有效，防止单行/单列时重复遍历。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(mn)，每个元素访问一次。
- 空间复杂度：O(1)，不计答案数组。

### 总结

螺旋遍历的核心是"边界收缩"的循环不变量。每轮保持 `t <= b && l <= r`，确保区间非空才执行对应方向的遍历。
