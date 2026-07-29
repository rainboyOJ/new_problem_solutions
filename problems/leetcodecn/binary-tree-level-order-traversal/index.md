---
oj: "leetcodecn"
problem_id: "binary-tree-level-order-traversal"
title: "二叉树的层序遍历"
difficulty: "普及+/提高"
tags: [二叉树, BFS, cpp, python]
description: "BFS 队列按当前层长度分组输出。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/binary-tree-level-order-traversal/
---
[[TOC]]
### 题意
按层从上到下返回二叉树节点值。
### 思路
BFS 队列，每轮记录当前队列长度，一次性处理一层。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
- 时间 O(n)，空间 O(n)
### 总结
层序遍历 = BFS + 按层分组输出。
