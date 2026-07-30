---
oj: "noi_openjudge"
problem_id: "ch0106-04"
title: "数组逆序重放"
description: "使用 reversed 逆序遍历输入数组，并由 print 自动空格分隔输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/04/
---

[[TOC]]

### 题意

将输入数组按相反顺序输出，元素之间以空格分隔。

### 思路

`reversed(numbers)` 提供逆序迭代器，`print(*...)` 会在展开后的元素间自动插入空格。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，除输入列表外额外空间复杂度为 $O(1)$。

### 总结

只需改变输出顺序时，使用逆序迭代不必修改原数组。
