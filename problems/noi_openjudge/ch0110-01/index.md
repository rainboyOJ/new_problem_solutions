---
oj: "noi_openjudge"
problem_id: "ch0110-01"
title: "谁考了第k名"
description: "按成绩降序排序，取下标为 k-1 的学生并用 g 格式输出分数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/01/
---

[[TOC]]

### 题意

给出每位学生互不相同的成绩，输出成绩第 $k$ 高的学号和分数。题目要求分数按 `%g` 的效果输出，不能固定小数位。

### 思路

把每位学生记成 `(学号, 成绩)`，按成绩降序排列。Python 列表下标从 `0` 开始，因此第 $k$ 名位于 `rank - 1`。

`f"{score:g}"` 与 C/C++ 的 `%g` 类似，会去掉不必要的小数末尾零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

排序时间复杂度为 $O(n \log n)$，额外空间复杂度为 $O(n)$。

### 总结

排序后直接按排名取元素。需要注意的是，名次从 `1` 开始而列表下标从 `0` 开始。
