---
oj: "leetcodecn"
problem_id: "flatten-binary-tree-to-linked-list"
title: "展开为链表"
difficulty: "普及+/提高"
tags: [二叉树, DFS, 栈, cpp, python]
description: "反向 preorder 递归原地接 prev，所有 left 置空。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/
---
[[TOC]]
### 题意
将二叉树原地展开为右指针链表（先序顺序）。
### 思路
反向先序（右-左-根）递归，用全局 prev 连接，所有左指针置空。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(height)。
### 总结
反向遍历配合 prev 指针是原地链表化的常用技巧。
