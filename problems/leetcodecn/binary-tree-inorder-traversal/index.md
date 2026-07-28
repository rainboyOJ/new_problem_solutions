---
oj: "leetcodecn"
problem_id: "binary-tree-inorder-traversal"
title: "二叉树的中序遍历"
description: "左根右；递归或显式栈模拟递归。"
difficulty: "简单"
date: 2026-07-28 22:05
toc: true
tags: ["二叉树", "栈", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/binary-tree-inorder-traversal/
---

[[TOC]]

### 题意

返回二叉树中序遍历的节点值序列。

### 思路

递归：左-根-右。迭代：显式栈模拟递归，先把左链全部入栈，弹出访问后转向右子树。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(n) 递归栈/显式栈。

### 总结

中序迭代栈是"沿左链入栈 → 弹出访问 → 转向右子树"三部曲，是后续很多树操作的基础。
