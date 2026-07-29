---
oj: "leetcodecn"
problem_id: "next-permutation"
title: "下一个排列"
description: "从右找下降点，找最小更大后继交换，反转后缀。"
difficulty: "普及+/提高"
date: 2026-07-29 13:03
toc: true
tags: ["技巧", "排列"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/next-permutation/
---

[[TOC]]

### 题意
求数组的下一个字典序排列。

### 思路
三步：1. 从右找到第一个下降点 `i`（`nums[i] < nums[i+1]`）；2. 从右找到第一个大于 `nums[i]` 的位置 `j`，交换；3. 反转 `i+1` 到末尾的后缀。

若完全降序则无下降点，直接反转整个数组。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
下一个排列的关键是"反转为最小"：交换后 `i` 后面的后缀仍然是降序的，反转即可变成升序（最小），保证是下一个排列。
