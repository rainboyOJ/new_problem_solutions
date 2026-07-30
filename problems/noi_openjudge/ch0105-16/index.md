---
oj: "noi_openjudge"
problem_id: "ch0105-16"
title: "买房子"
description: "逐年比较累计工资与当年房价，找出二十年内最早可购房年份。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/16/
---

[[TOC]]

### 题意

初始房价为 200 万，每年上涨 $K\%$；年薪 $N$ 万不变。求 20 年内最早能买房的年份。

### 思路

第 `year` 年开始时已攒下 `salary * year`，当前房价从 200 开始，若买不起再乘增长因子更新到下一年。按年从 1 到 20 模拟，第一次满足条件就是最早答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

最多模拟 20 年，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

“最早第几年”适合按时间顺序模拟；关键是统一工资累计和房价更新的时序。
