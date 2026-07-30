---
oj: "noi_openjudge"
problem_id: "ch0105-12"
title: "与指定数字相同的数的个数"
description: "把与目标值相等的布尔结果求和，得到出现次数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["统计", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/12/
---

[[TOC]]

### 题意

统计长度为 $N$ 的整数序列中等于指定数字的元素数量。

### 思路

表达式 `number == target` 的结果是布尔值，Python 中 `True`、`False` 可按 `1`、`0` 参与求和。因此 `sum(number == target for number in numbers)` 就是匹配数目。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，额外空间复杂度为 $O(1)$。

### 总结

布尔值求和是 Python 计数条件成立次数的常用模式。
