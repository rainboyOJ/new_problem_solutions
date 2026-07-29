---
oj: "leetcodecn"
problem_id: "palindrome-linked-list"
title: "回文链表"
description: "快慢指针找中点，反转后半段，与前半段比较，O(n) O(1)。"
difficulty: "入门"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "双指针", "栈", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/palindrome-linked-list/
---

[[TOC]]

### 题意

判断单链表是否为回文。

### 思路

数组存值再双指针 O(n) 空间。优化：快慢指针找到中间节点，反转后半段，逐节点比较。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1)。

### 总结

链表中点 + 反转是回文判断的标准做法。注意奇偶长度下中点的定位。
