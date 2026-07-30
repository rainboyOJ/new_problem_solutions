---
oj: "noi_openjudge"
problem_id: "ch0112-01"
title: "简单算术表达式求值"
description: "去除空格后识别唯一运算符，按对应整数运算规则计算结果。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/01/
---

[[TOC]]

### 题意

计算两个整数和一个运算符组成的简单表达式，运算符两侧可能有空格。

### 思路

先删除空格，再在五种运算符中找到出现的一个，用 `split` 分出左右操作数。根据运算符分支计算；`//` 对正整数正好是题目要求的整除。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间和空间复杂度均为 $O(1)$。

### 总结

输入格式固定且只有一个运算符时，直接解析比通用表达式求值更清楚。
