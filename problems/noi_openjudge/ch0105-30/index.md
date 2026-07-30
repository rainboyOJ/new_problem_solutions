---
oj: "noi_openjudge"
problem_id: "ch0105-30"
title: "含k个3的数"
description: "同时检查能否被 19 整除，以及十进制表示中数字 3 的出现次数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "整除", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/30/
---

[[TOC]]

### 题意

给定正整数 $m$ 和 $k$，判断 $m$ 是否能被 $19$ 整除，并且十进制表示中是否恰好有 $k$ 个数字 `3`。两个条件都满足时输出 `YES`。

### 思路

整除条件可直接用 `number % 19 == 0` 判断。把整数转换为字符串后，`str(number).count("3")` 就能统计数字 `3` 的出现次数。

两个条件使用 `and` 连接，只有都成立时才输出 `YES`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设 $m$ 有 $d$ 位，统计字符需要 $O(d)$ 时间，额外空间为 $O(d)$。

### 总结

同一输入需要满足多条性质时，分别写出每条布尔条件，再用逻辑运算组合，表达会清楚且易检查。
