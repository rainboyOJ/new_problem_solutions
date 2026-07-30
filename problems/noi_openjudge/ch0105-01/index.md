---
oj: "noi_openjudge"
problem_id: "ch0105-01"
title: "求平均年龄"
description: "用生成器累计 n 名学生年龄后除以人数并保留两位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/01/
---

[[TOC]]

### 题意

读入 $n$ 名学生的年龄，输出平均年龄，保留两位小数。

### 思路

平均值等于总和除以个数。生成器表达式依次读入 `n` 个年龄，`sum` 负责累计，不必手写临时累加变量；最后用 `.2f` 输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

连续读入并求和是 `sum(表达式 for ...)` 的典型场景。
