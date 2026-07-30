---
oj: "noi_openjudge"
problem_id: "ch0105-02"
title: "财务管理"
description: "累计固定 12 个月的余额并输出带美元符号的两位小数平均值。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/02/
---

[[TOC]]

### 题意

读入 12 个月的月末余额，输出平均余额，前缀为 `$`，保留两位小数。

### 思路

月份数量固定为 12。用 `sum(float(input()) for _ in range(12))` 累加，再除以 12；f-string 中先写 `$`，再用 `.2f` 保证货币格式。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

输入规模为常数时仍可用清晰的聚合写法，货币符号属于输出格式的一部分。
