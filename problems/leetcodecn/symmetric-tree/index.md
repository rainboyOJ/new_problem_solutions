---
oj: "leetcodecn"
problem_id: "symmetric-tree"
title: "对称二叉树"
description: "定义 mirror(a,b)：值相等且 a.left 对 b.right、a.right 对 b.left。"
difficulty: "简单"
date: 2026-07-28 22:05
toc: true
tags: ["二叉树", "递归", "BFS", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/symmetric-tree/
---

[[TOC]]

### 题意

判断二叉树是否轴对称（镜像对称）。

### 思路

递归定义：两棵树互为镜像当且仅当根值相等且 a.left 与 b.right 镜像、a.right 与 b.left 镜像。根节点的左右子树就是一对待检查的镜像。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(height)。

### 总结

对称树的递归定义本身就是镜像检查的算法。
