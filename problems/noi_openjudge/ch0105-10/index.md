---
oj: "noi_openjudge"
problem_id: "ch0105-10"
title: "满足条件的数累加"
description: "从不小于 m 的首个 17 倍数起每隔 17 累加。"
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
source: http://noi.openjudge.cn/ch0105/10/
---

[[TOC]]

### 题意

计算闭区间 $[m,n]$ 中所有能被 17 整除的数的和。

### 思路

不小于 `left` 的首个 17 倍数是 `(left + 16) // 17 * 17`。之后每次加 17，`range` 不会生成不满足整除条件的数；若首项超过右端点，空 range 的和自然为 0。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设区间内 17 的倍数个数为 $k$，时间复杂度为 $O(k)$，额外空间复杂度为 $O(1)$。

### 总结

整除筛选可以先定位第一个倍数，再按除数步进，减少无效检查。
