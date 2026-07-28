---
oj: "leetcodecn"
problem_id: "intersection-of-two-linked-lists"
title: "相交链表"
description: "双指针分别走 A+B 和 B+A，长度差被抵消后在交点或 nullptr 相遇。"
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
source: https://leetcode.cn/problems/intersection-of-two-linked-lists/
---

[[TOC]]

### 题意

找到两个单链表相交的起始节点。若不相交返回 nullptr。

### 思路

哈希集合存 A 节点再遍历 B 查找 O(m+n) 空间。双指针 O(1) 空间：两指针分别从 A、B 出发，走到尾后跳到另一链表头部。由于总路程 A+B = B+A，它们一定在交点或 nullptr 处相遇。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(m+n)。
- 空间复杂度：O(1)。

### 总结

走完自己的路再走别人的路——长度差被抵消，交汇处自然相遇。
