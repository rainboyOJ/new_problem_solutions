---
oj: "noi_openjudge"
problem_id: "ch0104-11"
title: "晶晶赴约会"
description: "用成员判断识别星期 1、3、5 的上课日。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/11/
---

[[TOC]]

### 题意

星期 1、3、5 有课，判断给定日期能否赴约。

### 思路

上课日是固定的小集合，`day in (1, 3, 5)` 直接表达成员关系。属于集合时输出 `NO`，否则输出 `YES`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

集合大小固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

比较固定的多个离散值时，成员判断比连续写多个 `or` 更清晰。
