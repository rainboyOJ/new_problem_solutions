---
oj: "noi_openjudge"
problem_id: "ch0107-04"
title: "石头剪子布"
description: "使用胜负映射判断每轮石头剪刀布，并输出 Player1、Player2 或 Tie。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/04/
---

[[TOC]]

### 题意

对每轮石头剪刀布输出胜者或平局。

### 思路

字典记录每种出拳战胜的对象。先判断相同出拳，再判断 Player1 的映射结果是否等于 Player2，剩余情况就是 Player2 胜。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，额外空间复杂度为 $O(1)$。

### 总结

用映射表描述固定胜负规则，可避免冗长的条件组合。
