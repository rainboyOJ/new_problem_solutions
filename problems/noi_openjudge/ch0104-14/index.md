---
oj: "noi_openjudge"
problem_id: "ch0104-14"
title: "计算邮资"
description: "基础邮资加超重部分的向上取整计费，再判断是否加急。"
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
source: http://noi.openjudge.cn/ch0104/14/
---

[[TOC]]

### 题意

1000 克以内收费 8 元；超出部分每 500 克或不足 500 克收费 4 元；加急另加 5 元。

### 思路

先初始化基础费。超重 `extra` 的计费段数是正整数向上除法 `(extra + 499) // 500`，再乘 4。最后独立判断加急字符是否为 `y`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

不足一个计费单位也收费时，要用向上取整而不是普通整除。
