---
oj: "leetcodecn"
problem_id: "construct-binary-tree-from-preorder-and-inorder-traversal"
title: "前序中序构树"
difficulty: "普及+/提高"
tags: [二叉树, 递归, 哈希表, cpp, python]
description: "前序首元素是根，用哈希表定位中序分界，递归构造区间。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
---
[[TOC]]
### 题意
根据前序和中序遍历结果构造二叉树。
### 思路
前序第一个为根，在中序中根左侧为左子树、右侧为右子树。哈希表加速定位。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(n)。
### 总结
前序定根、中序分左右是二叉树递归构造的基本模型。
