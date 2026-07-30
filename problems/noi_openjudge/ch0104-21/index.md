---
oj: "noi_openjudge"
problem_id: "ch0104-21"
title: "苹果和虫子2"
description: "向上取整统计已被吃或正在被吃的苹果，并将剩余数下限限制为零。"
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
source: http://noi.openjudge.cn/ch0104/21/
---

[[TOC]]

### 题意

每 $x$ 小时吃完一个苹果，经过 $y$ 小时求剩余完整苹果数；输入不保证剩余数非负。

### 思路

被吃或正在吃的苹果数是 $\lceil y/x\rceil$，正整数向上除法为 `(y + x - 1) // x`。第 2 版还要用 `max(0, ...)` 防止答案小于零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

当题目允许耗时超过库存时，除了向上取整，还要显式处理结果下界。
