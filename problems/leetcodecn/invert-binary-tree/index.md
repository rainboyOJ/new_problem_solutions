---
oj: "leetcodecn"
problem_id: "invert-binary-tree"
title: "翻转二叉树"
description: "后序/前序递归交换左右子树。"
difficulty: "入门"
date: 2026-07-28 22:05
toc: true
tags: ["二叉树", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/invert-binary-tree/
---

[[TOC]]

### 题意

翻转二叉树（镜像对称）。

### 思路

递归：交换当前节点的左右子树，然后递归翻转左右子树。前序和后序都可以，中序需要特殊处理。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(height)。

### 总结

翻转二叉树是递归思维的经典入门练习——先交换、再递归处理子树。
