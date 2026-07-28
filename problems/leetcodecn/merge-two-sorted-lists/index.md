---
oj: "leetcodecn"
problem_id: "merge-two-sorted-lists"
title: "合并两个有序链表"
description: "dummy 头结点，每次接入较小节点，最后接剩余链。"
difficulty: "简单"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/merge-two-sorted-lists/
---

[[TOC]]

### 题意

合并两个升序链表，返回新链表。

### 思路

迭代：dummy 头结点简化边界处理，每次选取较小节点接入，最后将剩余链直接接上。

递归：每次选较小节点，递归合并剩余部分。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n+m)。
- 空间复杂度：O(1) 迭代，O(n+m) 递归。

### 总结

dummy 头结点是链表操作中处理边缘条件（空链表、删头节点等）的标准技巧。
