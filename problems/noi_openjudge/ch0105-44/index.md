---
oj: "noi_openjudge"
problem_id: "ch0105-44"
title: "第n小的质数"
description: "用埃氏筛找出不超过第 10000 个质数的全部质数，再按下标取第 n 个。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["质数", "筛法", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/44/
---

[[TOC]]

### 题意

输入 $n\leqslant10000$，输出第 $n$ 小的质数。

### 思路

第 $10000$ 个质数是 $104729$，因此筛到这个上界即可覆盖所有输入。埃氏筛从每个尚未筛掉的 `number` 的平方开始，将其倍数标记为合数；最后收集仍为真的下标。

题目序号从 $1$ 开始，而 Python 列表从 $0$ 开始，所以答案是 `primes[rank - 1]`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设筛法上界为 $U=104729$，时间复杂度为 $O(U\log\log U)$，空间复杂度为 $O(U)$。

### 总结

需要连续多个质数时，预处理筛法比对每个候选数重复试除更合适。
