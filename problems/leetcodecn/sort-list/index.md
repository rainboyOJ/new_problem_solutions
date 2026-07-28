---
oj: "leetcodecn"
problem_id: "sort-list"
title: "排序链表"
description: "快慢指针拆半，递归归并排序，O(n log n) 时间 O(log n) 递归空间。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "排序", "归并排序", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/sort-list/
---

[[TOC]]

### 题意

对链表排序，要求 O(n log n) 时间、O(1) 额外空间。

### 思路

数组排序 O(n) 辅助空间。归并排序满足要求：快慢指针找中点分割，递归排序两半，合并两个有序链表。递归深度 O(log n)。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n log n)。
- 空间复杂度：O(log n) 递归栈。

### 总结

链表归并排序是"寻中-递归-合并"三步曲，核心是利用链表 O(1) 拆分和 O(n) 合并的特性。
