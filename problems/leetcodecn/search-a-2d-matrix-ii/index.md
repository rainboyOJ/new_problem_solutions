---
oj: "leetcodecn"
problem_id: "search-a-2d-matrix-ii"
title: "搜索二维矩阵 II"
description: "从右上角出发，小于 target 向下，大于 target 向左，每步排除一行或一列，O(m+n)。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "二分查找", "分治", "矩阵", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/search-a-2d-matrix-ii/
---

[[TOC]]

### 题意

m×n 矩阵，每行从左到右递增，每列从上到下递增。查找 target 是否存在。

### 思路

暴力 O(mn)。利用矩阵的递增特性：从右上角开始，如果当前值小于 target 则向下（行递增），大于 target 则向左（列递减）。每步排除一行或一列，O(m+n)。

该思路与第 74 题（整体有序）不同：74 题的矩阵可扁平化为有序数组直接二分，而本题每行独立递增但跨行不保证连续。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(m+n)，每步排除一行或一列。
- 空间复杂度：O(1)。

### 总结

"右上角出发逐步缩小搜索范围"是杨氏矩阵搜索的标准方法，每次比较都能排除一整行或一整列。
