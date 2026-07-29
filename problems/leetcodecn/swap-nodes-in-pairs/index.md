---
oj: "leetcodecn"
problem_id: "swap-nodes-in-pairs"
title: "两两交换链表中的节点"
description: "dummy + prev/a/b/next 四指针每轮重连已交换段和待处理段。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/swap-nodes-in-pairs/
---

[[TOC]]

### 题意

两两交换链表中的相邻节点，返回头节点。不能只交换值。

### 思路

dummy 头结点下，每轮维护 `prev -> a -> b -> next` 四个指针，把 a 和 b 交换后接入。注意最后 `prev` 移动到 a 的位置，因为 a 已成为已交换段的尾节点。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1)。

### 总结

两两交换是"K 个一组翻转"的特例（k=2），掌握 k=2 的指针重连后推广到一般 k。
