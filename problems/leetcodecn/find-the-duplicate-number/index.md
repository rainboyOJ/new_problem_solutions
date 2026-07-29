---
oj: "leetcodecn"
problem_id: "find-the-duplicate-number"
title: "寻找重复数"
description: "把值视为 next 指针，Floyd 找环入口即为重复数。"
difficulty: "提高+/省选-"
date: 2026-07-29 13:04
toc: true
tags: ["快慢指针", "链表", "技巧"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/find-the-duplicate-number/
---

[[TOC]]

### 题意
在 n+1 个元素（值域 [1,n]）中找重复数，不修改数组，O(1) 空间。

### 思路
把 `nums[i]` 视为从 `i` 到 `nums[i]` 的 next 指针，数组构成一个有环链表（重复值导致两个节点指向同一后继）。Floyd 快慢指针找环入口即为重复数。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
把数组值视为 next 指针是本题的关键映射。重复数意味着两个位置指向同一个后继，形成环。Floyd 找环入口的证明与链表环检测完全相同。
