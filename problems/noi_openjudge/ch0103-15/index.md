---
oj: "noi_openjudge"
problem_id: "ch0103-15"
title: "苹果和虫子"
description: "用整数向上除法统计被吃完的苹果数量并从总数中扣除。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/15/
---

[[TOC]]

### 题意

每 $x$ 小时虫子吃完一个苹果。经过 $y$ 小时，求剩余的完整苹果数。

### 思路

只要正在吃某个苹果，它就不再完整，因此被影响的苹果数为 $\lceil y/x\rceil$。正整数向上除法写成 `(y + x - 1) // x`，从 `n` 中减去它即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

“剩余完整物品”要把已开始但未完成的操作也计入损失，因此使用向上取整。
