---
oj: "luogu"
problem_id: "P1425"
title: "小鱼的游泳时间"
description: "统一换成总分钟数后直接相减。"
difficulty: "入门"
date: 2026-06-18 20:30
toc: true
tags: ["模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1425
---

[[TOC]]

### 题意

给出开始时间 `a` 时 `b` 分和结束时间 `c` 时 `d` 分，求这段时间一共经过了多少小时多少分钟。

### 思路

先看一个可以直接验证想法的朴素解：

把开始和结束时间都换算成总分钟数，再做减法。

@include-code(./brute.cpp, cpp)

这题没有复杂优化，关键是别在“时”和“分”之间手工借位，统一成分钟后最稳。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度是 $O(1)$，空间复杂度也是 $O(1)$。

### 总结

这题就是一个标准的时间差计算，把两个时间点都转成总分钟数即可。
