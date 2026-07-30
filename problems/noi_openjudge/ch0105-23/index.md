---
oj: "noi_openjudge"
problem_id: "ch0105-23"
title: "药房管理"
description: "按请求顺序扣减库存，库存不足时计数但不改变库存。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/23/
---

[[TOC]]

### 题意

给定初始库存和按顺序到来的取药请求，统计因库存不足而被拒绝的病人数。

### 思路

逐个处理请求。请求量超过当前库存时增加拒绝计数，库存不变；否则扣减库存。这是典型的单状态顺序模拟。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

库存模拟的关键是拒绝请求不能消耗库存，状态只在成功操作后更新。
