---
oj: "noi_openjudge"
problem_id: "ch0105-28"
title: "分离整数的各个数位"
description: "把整数的十进制字符串逆序，再用空格连接各个数字。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "数位", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/28/
---

[[TOC]]

### 题意

输入一个正整数，从个位到最高位依次输出它的每一位，并在相邻数字之间输出一个空格。

### 思路

输入本身就是从高位到低位排列的十进制字符串。`reversed(number)` 依次给出从低位到高位的字符，`" ".join(...)` 负责在相邻字符间插入一个空格。

这样不需要特判最后一个数字，也无需手动维护输出格式。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设数字有 $d$ 位，时间复杂度为 $O(d)$，输出字符串占用 $O(d)$ 空间。

### 总结

仅需按位展示而不做数值计算时，保留字符串形式最简洁，也不会受整数运算影响。
