---
oj: "leetcodecn"
problem_id: "product-of-array-except-self"
title: "除自身以外数组的乘积"
description: "结果先存左侧前缀积，再乘右侧后缀积，O(n) 时间 O(1) 额外空间。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "前缀和", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/product-of-array-except-self/
---

[[TOC]]

### 题意

返回数组 answer，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。不能用除法，O(n) 时间。

### 思路

最简单想到的是 O(n²) 暴力或先算总积再除以自身（但题目禁止除法且零元素会导致除零）。优化：第一次遍历存左侧前缀积到答案数组，第二次遍历从右侧乘上后缀积。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)，两次遍历。
- 空间复杂度：O(1) 不计答案数组。

### 总结

"左侧前缀 + 右侧后缀"是避免除法的经典技巧，不需要特殊处理零元素。
