---
oj: "leetcodecn"
problem_id: "add-two-numbers"
title: "两数相加"
description: "同步遍历两链表和进位，节点值写 sum % 10，末尾保留 carry。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "数学", "递归", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/add-two-numbers/
---

[[TOC]]

### 题意

两个逆序存储的非负整数链表，每位存一个数字，求和并以相同形式返回。

### 思路

同步遍历两个链表，逐位相加并处理进位。注意长度不等时补 0 处理，最后如果还有进位要新增节点。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(max(n,m))。
- 空间复杂度：O(1)，不计结果空间。

### 总结

链表大数加法的关键在于统一处理"长度不同"和"末尾进位"两个边界。
