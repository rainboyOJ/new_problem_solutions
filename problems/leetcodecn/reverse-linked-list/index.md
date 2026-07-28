---
oj: "leetcodecn"
problem_id: "reverse-linked-list"
title: "反转链表"
description: "prev/cur/next 三指针逐节点反转，同时保留后续节点引用。"
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
source: https://leetcode.cn/problems/reverse-linked-list/
---

[[TOC]]

### 题意

反转单链表。

### 思路

迭代：用 `prev` 和 `cur` 两个指针，每次保存 `cur->next` 后反转指向。递归：`head->next` 后的链表已反转，将 `head` 接到末尾。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1) 迭代，O(n) 递归栈。

### 总结

反转链表是链表操作的基本功。迭代三指针是基础版本，递归反转的核心在于"相信子问题已被解决"。
