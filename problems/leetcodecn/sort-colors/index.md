---
oj: "leetcodecn"
problem_id: "sort-colors"
title: "颜色分类"
description: "三指针荷兰国旗：p0 指向 0 的右界，p2 指向 2 的左界，扫描指针交换后分类推进。"
difficulty: "普及+/提高"
date: 2026-07-29 13:02
toc: true
tags: ["双指针", "排序"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/sort-colors/
---

[[TOC]]

### 题意
只含 0、1、2 的数组，一趟扫描原地排序。

### 思路
荷兰国旗问题：`p0` 指向已放好的 0 的右界，`p2` 指向已放好的 2 的左界，`i` 扫描。遇到 0 与 `p0` 交换并推进两者；遇到 2 与 `p2` 交换但只推进 `p2`（交换过来的可能是 0，需要再处理）。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
三路划分（荷兰国旗）的核心是三个区间的边界维护。遇到 2 交换后不推进 `i`，因为交换过来的值需要再判断。
