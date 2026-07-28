---
oj: "leetcodecn"
problem_id: "kth-smallest-element-in-a-bst"
title: "BST 第 K 小"
difficulty: "中等"
tags: [BST, 中序, 栈, cpp, python]
description: "BST 中序有序，迭代栈访问到第 k 个就停止。"
---
[[TOC]]
### 题意
返回 BST 中第 k 小的元素。
### 思路
BST 中序遍历 = 升序序列。用迭代栈遍历到第 k 个即返回。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(H + k)，空间 O(H)。
### 总结
BST 的中序性质让第 k 小问题变成"控制中序遍历的终止时机"。
