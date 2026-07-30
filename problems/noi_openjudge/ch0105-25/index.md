---
oj: "noi_openjudge"
problem_id: "ch0105-25"
title: "求特殊自然数"
description: "枚举两种进制均为三位数的公共范围，比较七进制与反向九进制。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["枚举", "进制", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/25/
---

[[TOC]]

### 题意

求一个自然数，使其七进制和九进制表示均为三位，且两种表示的数字顺序恰好相反。

### 思路

三位九进制数至少为 $9^2$，三位七进制数小于 $7^3$，只需枚举公共区间。`to_base` 用反复取余生成低位，再反转得到正常表示；比较 `base7 == base9[::-1]` 即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

枚举范围固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

进制转换的基本过程是反复取余；从低位收集后反转即可恢复高位到低位顺序。
