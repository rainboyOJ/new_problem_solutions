---
oj: "leetcodecn"
problem_id: "linked-list-cycle"
title: "环形链表"
description: "Floyd 快慢指针，slow 走一步 fast 走两步，相遇则有环。"
difficulty: "简单"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "双指针", "哈希表", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/linked-list-cycle/
---

[[TOC]]

### 题意

判断链表是否有环。

### 思路

哈希集合记录已访问节点 O(n) 空间。Floyd 快慢指针 O(1) 空间：慢指针每次走一步，快指针每次走两步，若有环则必相遇。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1)。

### 总结

Floyd 判环是快慢指针的经典应用。快指针每轮多走一步，在环内一定能追上慢指针。
