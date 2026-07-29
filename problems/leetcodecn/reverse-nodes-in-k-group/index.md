---
oj: "leetcodecn"
problem_id: "reverse-nodes-in-k-group"
title: "K 个一组翻转链表"
description: "先找第 k 个节点，翻转这一段并接回；不足 k 段保持原样。"
difficulty: "提高+/省选-"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/reverse-nodes-in-k-group/
---

[[TOC]]

### 题意

每 k 个节点一组翻转链表，不足 k 的保持原样。

### 思路

递归版：先检查是否有 k 个节点，有则递归处理后续部分，再翻转当前段。迭代版更节省空间：用 dummy 和 prev 指针维护已翻转到未处理的边界，每轮找到第 k 个节点后翻转段内指针。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)。
- 空间复杂度：O(1) 迭代，O(n/k) 递归。

### 总结

K 个一组翻转是链表操作的综合练习，需要同时处理"寻找段尾"、"段内翻转"、"衔接前后"三个子任务。
