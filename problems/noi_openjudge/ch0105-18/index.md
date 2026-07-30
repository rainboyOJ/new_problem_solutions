---
oj: "noi_openjudge"
problem_id: "ch0105-18"
title: "鸡尾酒疗法"
description: "比较改进疗法与基准疗法有效率之差是否严格超过 5%。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/18/
---

[[TOC]]

### 题意

第一组是基准疗法，比较每个新疗法的有效率差，严格大于 5% 为 `better`，严格小于 -5% 为 `worse`。

### 思路

不要直接比较浮点有效率，5% 边界会受二进制误差影响。将差值通分：`effective * base_total - base_effective * total`，再交叉相乘比较它是否严格超过分母的 5%。等于 5% 时仍为 `same`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

比较比例变化时应直接比较差值，并严格区分“大于阈值”和“等于阈值”。
