---
oj: "leetcodecn"
problem_id: "3sum"
title: "三数之和"
description: "排序后固定第一个数，剩余区间用双指针，跳过相同值去重，O(n²)。"
difficulty: "普及+/提高"
date: 2026-07-28 22:03
toc: true
tags: ["双指针", "排序", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/3sum/
---

[[TOC]]

### 题意

找出数组中所有和为 0 且不重复的三元组。

### 思路

三重循环枚举 O(n³) 会超时。排序后固定第一个数，在剩余区间中用双指针寻找两数之和等于 `-nums[i]`。

去重是关键：排序后，每层循环（第一个数、左指针、右指针）在移动时跳过相同值，避免重复三元组。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n²)，排序 O(n log n)，双指针 O(n²)。
- 空间复杂度：O(1)，不计答案空间。

### 总结

三数之和是两数之和的推广：固定一个数转化为两数之和问题，再套用双指针。排序辅助去重的做法比用哈希集合去重更干净。
