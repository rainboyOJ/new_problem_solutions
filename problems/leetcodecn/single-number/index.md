---
oj: "leetcodecn"
problem_id: "single-number"
title: "只出现一次的数字"
description: "异或所有元素，成对元素异或为 0，最终结果即为只出现一次的数。"
difficulty: "入门"
date: 2026-07-29 13:00
toc: true
tags: ["位运算", "技巧"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/single-number/
---

[[TOC]]

### 题意
找出数组中唯一只出现一次的数（其余均出现两次）。

### 思路
利用异或性质：`x ^ x = 0`，`x ^ 0 = x`，异或满足交换律和结合律。将所有元素异或起来，成对元素互相抵消，结果就是只出现一次的数。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
异或去重是位运算的经典技巧：`x ^ x = 0` 保证成对元素消除，`x ^ 0 = x` 保证结果保留。
