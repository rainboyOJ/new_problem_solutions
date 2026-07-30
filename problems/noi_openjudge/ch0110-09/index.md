---
oj: "noi_openjudge"
problem_id: "ch0110-09"
title: "明明的随机数"
description: "用 set 去重后排序，输出不同随机数的个数和升序序列。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "集合", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/09/
---

[[TOC]]

### 题意

删除随机数中的重复值，再将剩余数字从小到大输出，并先输出不同数字的个数。

### 思路

`set` 会自动只保留每个整数的一份，`sorted(set(...))` 再把无序集合转为升序列表。列表长度就是不同数字的个数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

去重平均时间为 $O(n)$，排序时间为 $O(m \log m)$，其中 $m$ 是不同数字的个数；空间复杂度为 $O(m)$。

### 总结

只需要“去重后再排序”时，`sorted(set(values))` 是清楚且常用的组合。
