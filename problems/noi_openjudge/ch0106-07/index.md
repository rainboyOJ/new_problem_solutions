---
oj: "noi_openjudge"
problem_id: "ch0106-07"
title: "有趣的跳跃"
description: "收集相邻差的绝对值，用集合判断其是否恰好为 1 到 n-1。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "集合", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/07/
---

[[TOC]]

### 题意

若长度为 $n$ 的序列相邻差绝对值排序后恰好是 $1$ 到 $n-1$，输出 `Jolly`，否则输出 `Not jolly`。

### 思路

用 `zip(numbers, numbers[1:])` 枚举相邻对，收集绝对差到集合。若集合恰好等于 `set(range(1, length))`，说明每个要求的差都出现过且没有重复或越界值。

当 $n=1$ 时，两边都是空集合，也自然得到 `Jolly`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，集合使用 $O(n)$ 空间。

### 总结

判定一组值是否刚好构成目标集合时，集合相等比较简洁且能同时检查重复。
