---
oj: "noi_openjudge"
problem_id: "ch0106-05"
title: "年龄与疾病"
description: "按年龄上界分类计数，再除以总人数输出四组百分比。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "分类讨论", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/05/
---

[[TOC]]

### 题意

将患者年龄分为 $0$-$18$、$19$-$35$、$36$-$60$ 和不小于 $61$ 四组，输出每组所占百分比。

### 思路

从小到大判断年龄上界即可确定唯一分组。记录四组人数后，用 `count * 100 / patient_count` 计算比例并格式化为两位小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，额外空间复杂度为 $O(1)$。

### 总结

连续区间分类时，按边界递增的 `if` / `elif` 链最容易保证不重不漏。
