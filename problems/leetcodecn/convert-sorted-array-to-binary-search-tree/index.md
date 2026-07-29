---
oj: "leetcodecn"
problem_id: "convert-sorted-array-to-binary-search-tree"
title: "有序数组转 BST"
difficulty: "入门"
tags: [BST, 递归, 分治, cpp, python]
description: "取中点为根，递归构造左右半段，天然平衡。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
---
[[TOC]]
### 题意
将升序数组转换为高度平衡的 BST。
### 思路
每次取中间元素为根，递归构造左右子树。中序遍历结果即为原数组。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(log n) 递归栈。
### 总结
有序数组转 BST 的本质是二分递归。
