---
oj: "noi_openjudge"
problem_id: "ch0111-07"
title: "和为给定数"
description: "排序后使用左右指针寻找和为目标值的数对。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "双指针", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/07/
---

[[TOC]]

### 题意

在整数序列中找一对数使其和为给定值；有多组时输出较小数最小的一组。

### 思路

先升序排序。左右指针的和偏小时左指针右移，偏大时右指针左移；相等时直接输出。左指针从最小数开始推进，因此第一次找到的数对具有最小的较小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

排序为 $O(n \log n)$，双指针扫描为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

有序序列中的两数之和可通过一增一减的双指针在线性时间内完成。
