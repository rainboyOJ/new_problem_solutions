---
oj: "leetcodecn"
problem_id: "set-matrix-zeroes"
title: "矩阵置零"
description: "用首行/首列充当标记位，先记录首行首列是否含零，再标记并回填，O(1) 额外空间。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "矩阵", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/set-matrix-zeroes/
---

[[TOC]]

### 题意

m×n 矩阵，如果某元素为 0，将其所在行和列全部置零。原地修改。

### 思路

用额外行列集合记录零位置 O(m+n) 空间。O(1) 空间优化：用矩阵首行首列作为标记位，先单独记录首行首列本身是否含零，再用首行首列标记其他行列是否有零，最后回填。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(mn)，遍历矩阵两次。
- 空间复杂度：O(1)。

### 总结

"借用已有空间作标记"是原地算法的常见技巧，关键在于防止标记本身被提前覆盖。
