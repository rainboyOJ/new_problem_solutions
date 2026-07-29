---
oj: "leetcodecn"
problem_id: "maximum-depth-of-binary-tree"
title: "二叉树的最大深度"
description: "1 + max(left, right) 递归。"
difficulty: "入门"
date: 2026-07-28 22:05
toc: true
tags: ["二叉树", "递归", "BFS", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/maximum-depth-of-binary-tree/
---

[[TOC]]

### 题意

返回二叉树的最大深度（根到最远叶子节点的路径长度）。

### 思路

递归：空节点深度 0，非空节点深度 = 1 + max(左子树深度, 右子树深度)。

BFS 层序遍历也可以统计深度。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(height) 递归栈。

### 总结

树的最大深度是树形 DP 的最简单例子——通过子问题定义"以某节点为根的子树深度"。
