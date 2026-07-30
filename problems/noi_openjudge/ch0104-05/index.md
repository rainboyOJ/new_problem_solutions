---
oj: "noi_openjudge"
problem_id: "ch0104-05"
title: "整数大小比较"
description: "按大于、等于、小于的顺序比较两个整数并输出关系符号。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/05/
---

[[TOC]]

### 题意

比较两个整数，输出 `>`、`=` 或 `<`。

### 思路

先判断 `x > y`，否则判断是否相等，最后剩余情况就是 `x < y`。代码使用嵌套条件表达式表达这三个互斥结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

三路比较要覆盖相等分支，不能只写大于和小于。
