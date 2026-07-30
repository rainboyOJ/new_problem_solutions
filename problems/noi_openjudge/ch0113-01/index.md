---
oj: "noi_openjudge"
problem_id: "ch0113-01"
title: "数制转换"
description: "先用 int 按原进制解析，再用除基取余将结果转换为目标进制。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["进制转换", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/01/
---

[[TOC]]

### 题意

将 2 到 16 进制的非负整数转换到另一个进制，字母部分统一使用大写输出。

### 思路

Python 的 `int(text, base)` 可直接将原进制数字转为整数。再不断执行 `divmod(value, target_base)`，余数就是从低到高的目标进制位，最后反转即可。零要单独处理。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设输出位数为 $k$，时间复杂度为 $O(k)$，空间复杂度为 $O(k)$。

### 总结

进制转换可拆成“解析为数值”和“数值重新编码”两个独立步骤。
