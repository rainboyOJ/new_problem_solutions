---
oj: "noi_openjudge"
problem_id: "ch0106-13"
title: "大整数的因子"
description: "用逐位取模递推计算大整数对 2 至 9 的余数，输出所有因子。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["高精度", "数学", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/13/
---

[[TOC]]

### 题意

给定最多 $30$ 位的非负整数，输出 $2$ 到 $9$ 中能整除它的所有数；没有则输出 `none`。

### 思路

对每个候选除数，从左到右维护已读前缀的余数。读入下一位 `digit` 后，新余数为 `(remainder * 10 + digit) % divisor`。最终余数为零便说明整除。

这种写法不依赖把整串数字转为整数，也适用于更长的十进制数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设数字长度为 $d$，候选除数固定为 $8$ 个，时间复杂度为 $O(d)$，额外空间复杂度为 $O(1)$。

### 总结

逐位取模是处理超长整数整除性的通用模板。
