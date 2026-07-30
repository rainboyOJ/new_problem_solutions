---
oj: "noi_openjudge"
problem_id: "ch0105-09"
title: "奇数求和"
description: "从区间内首个奇数起每次加 2，累计所有奇数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/09/
---

[[TOC]]

### 题意

计算闭区间 $[m,n]$ 中所有奇数的和。

### 思路

若左端点为偶数，首个奇数是 `left + 1`，否则就是 `left`。之后奇数间隔恒为 2，`range(first_odd, right + 1, 2)` 只生成需要累加的数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设区间内奇数数目为 $k$，时间复杂度为 $O(k)$，额外空间复杂度为 $O(1)$。

### 总结

筛选固定步长序列时，应让 `range` 的起点和步长直接表达筛选规则。
