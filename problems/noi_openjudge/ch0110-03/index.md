---
oj: "noi_openjudge"
problem_id: "ch0110-03"
title: "成绩排序"
description: "使用二元排序键，先按成绩降序，再按姓名字典序升序排列。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/03/
---

[[TOC]]

### 题意

将成绩单按分数从高到低排列；同分时姓名字典序较小的学生在前。

### 思路

Python 的元组会从左到右比较。排序键写成 `(-分数, 姓名)`：负号把分数的升序改为降序，姓名仍按默认字典序升序比较。这样一条 `sort` 就表达了两级规则。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，排序额外空间复杂度为 $O(n)$。

### 总结

多关键字排序的关键是把每层规则依次写进元组键中。
