---
oj: "leetcodecn"
problem_id: "copy-list-with-random-pointer"
title: "随机链表的复制"
description: "哈希表映射旧节点到新节点，第二遍补 next/random 引用。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "哈希表", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/copy-list-with-random-pointer/
---

[[TOC]]

### 题意

复制带随机指针的链表，返回深拷贝。random 指针可指向任意节点或 null。

### 思路

哈希表第一遍遍历创建所有新节点并建立映射，第二遍遍历补全 next 和 random。O(n) 时间 O(n) 空间。

进阶：节点交错插入法（旧->新->旧->新...）可做到 O(1) 额外空间。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(n)。

### 总结

拷贝指针问题中哈希表是最直观的解法。交错插入法优化了空间，但增加了实现复杂度。
