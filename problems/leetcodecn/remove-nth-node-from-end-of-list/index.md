---
oj: "leetcodecn"
problem_id: "remove-nth-node-from-end-of-list"
title: "删除链表的倒数第 N 个结点"
description: "dummy + 快慢指针相距 n+1，快指针到尾时慢指针在待删节点前一位。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "双指针", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
---

[[TOC]]

### 题意

删除链表倒数第 n 个节点，返回头节点。

### 思路

两次遍历版：先求长度再删除。一次遍历版：dummy + 快慢指针，快指针先走 n 步，然后两指针同步走，快指针到尾部时慢指针刚好在待删节点的前一个节点。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1)。

### 总结

快慢指针定位倒数第 k 个元素是链表的经典技巧。dummy 节点统一处理删头节点的边界情况。
