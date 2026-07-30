---
oj: "noi_openjudge"
problem_id: "ch0104-08"
title: "判断一个数能否同时被3和5整除"
description: "同时被 3 和 5 整除等价于能被它们的最小公倍数 15 整除。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/08/
---

[[TOC]]

### 题意

判断整数能否同时被 3 和 5 整除。

### 思路

因为 3 和 5 互质，同时整除等价于 `number % 15 == 0`。也可写两个取余判断并用 `and`，但最小公倍数写法更短。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

判断同时整除时，可以用最小公倍数合并条件。
