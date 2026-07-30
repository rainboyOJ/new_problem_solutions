---
oj: "noi_openjudge"
problem_id: "ch0110-02"
title: "奇数单增序列"
description: "用列表推导式筛出奇数，再排序并用逗号连接输出。"
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
source: http://noi.openjudge.cn/ch0110/02/
---

[[TOC]]

### 题意

从给定正整数序列中保留所有奇数，按升序输出，元素之间必须用逗号分隔。

### 思路

列表推导式在读入时完成筛选：`number % 2 == 1` 的数就是奇数。对结果调用 `sorted`，最后将整数转为字符串，用 `",".join(...)` 统一控制分隔符，避免处理末尾逗号。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设筛出的奇数个数为 $m$，时间复杂度为 $O(n + m \log m)$，空间复杂度为 $O(m)$。

### 总结

当输出格式有固定分隔符时，`join` 比逐项输出更简洁，也不会多输出一个逗号。
