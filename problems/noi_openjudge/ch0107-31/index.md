---
oj: "noi_openjudge"
problem_id: "ch0107-31"
title: "字符串p型编码"
description: "线性扫描数字串，统计每段相同连续字符的长度并输出计数和字符。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/31/
---

[[TOC]]

### 题意

对数字串做 p 型编码：每段连续相同字符输出“重复次数 + 字符”。

### 思路

维护当前连续段的 `count`。扫描到不同字符或字符串末尾时，输出上一段，再将计数重置为 $1$。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，输出空间为 $O(n)$。

### 总结

处理连续段时，把“到达末尾”与“遇到不同字符”统一为一段结束条件。
