---
oj: "leetcodecn"
problem_id: "binary-tree-maximum-path-sum"
title: "二叉树最大路径和"
difficulty: "困难"
tags: [二叉树, 树形DP, 递归, cpp, python]
description: "递归返回向下最大贡献 max(0,child)，经过点的两侧贡献更新全局答案。"
---
[[TOC]]
### 题意
路径可以从任意节点开始到任意节点结束，求路径和最大值。
### 思路
后序返回"以该节点为端点的向下最大单侧和"（负数视为 0），经过当前节点的候选为 left + right + val，全局更新。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(height)。
### 总结
与直径问题统一为"后序返回单侧、全局更新跨点答案"的树形 DP 模式。
