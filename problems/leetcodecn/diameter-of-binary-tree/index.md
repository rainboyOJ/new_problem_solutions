---
oj: "leetcodecn"
problem_id: "diameter-of-binary-tree"
title: "二叉树的直径"
description: "后序返回高度，经过当前点的候选为 left+right，全局取最大。"
difficulty: "入门"
date: 2026-07-28 22:05
toc: true
tags: ["二叉树", "递归", "树形DP", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/diameter-of-binary-tree/
---

[[TOC]]

### 题意

二叉树直径 = 任意两节点间最长路径的边数。

### 思路

对每个节点，经过它的最长路径 = 左子树最大深度 + 右子树最大深度。DFS 后序返回子树深度，同时全局更新答案。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(height)。

### 总结

"后序返回单侧值、全局更新跨双侧答案"是树形 DP 的基础模式，二叉树的直径和最大路径和都沿用此模型。
