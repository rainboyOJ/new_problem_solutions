---
oj: "leetcodecn"
problem_id: "linked-list-cycle-ii"
title: "环形链表 II"
description: "Floyd 判环后，从头和相遇点各走一步，第二次相遇即入环点。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "双指针", "哈希表", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/linked-list-cycle-ii/
---

[[TOC]]

### 题意

返回链表开始入环的第一个节点。无环返回 nullptr。

### 思路

快慢指针相遇后，慢指针从头重新走，快指针从相遇点继续走（每次一步），再次相遇处即入环节点。

数学推导：设环前长度 a，环长 b，相遇时 slow 走了 a + x，fast 走了 a + x + kb。由 `2(a+x) = a+x+kb` 得 `a = (k-1)b + (b-x)`，所以从头和相遇点同步走一定在入环点相遇。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1)。

### 总结

Floyd 判环的进阶版，利用距离关系找到环的入口。
