---
oj: "leetcodecn"
problem_id: "search-a-2d-matrix"
title: "搜索二维矩阵"
description: "把二维下标映射到一维有序序列，一次二分查找 target。"
difficulty: "普及-"
date: 2026-07-29 11:48
toc: true
tags: ["二分查找", "矩阵"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/search-a-2d-matrix/
---

[[TOC]]

### 题意

给定满足"每行递增、每行首元素大于上一行末元素"的 `m x n` 矩阵，判断 `target` 是否存在。要求 $O(\log(mn))$。

### 思路

矩阵的行间递增性质使得整行拼起来就是一个严格递增的一维数组。因此只需把一维下标 `k` 映射到二维：`matrix[k / n][k % n]`，然后对 `k` 做标准二分查找即可。

映射公式：`k ∈ [0, m*n)`，行号 `k / n`，列号 `k % n`。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log(mn))$。
- 空间复杂度：$O(1)$。

### 总结

二维矩阵的二分查找，核心是建立一维到二维的下标映射。前提是矩阵满足行间递增的严格条件，这样一维展开后仍有序。
