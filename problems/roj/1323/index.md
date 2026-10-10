---
oj: "roj"
problem_id: "1323"
title: "活动选择"
description: "按结束时间升序贪心选相容区间，求最大活动数。"
difficulty: "入门"
date: 2026-09-30 05:05
updated: 2026-10-05 09:42
toc: true
tags: ["贪心", "区间调度", "排序"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1323
---

[[TOC]]

## 题目描述

学校有 $n$（$n \le 1000$）个活动都想用同一间礼堂，同一时间只能安排一个。给定每个活动的起始时间 $begin_i$ 和结束时间 $end_i$（$begin_i < end_i \le 32767$），挑出尽可能多的活动使它们两两不冲突，输出这个最大数量。

样例输入：

```
11 3 5 1 4 12 14 8 12 0 6 8 11 6 10 5 7 3 8 5 9 2 13
```

样例输出：`4`。

## 思路

经典区间调度：把所有活动按结束时间升序排序后扫描，维护已选活动的最大结束时刻 `last_end`，凡是 `begin_i >= last_end` 的就贪心选上，最终统计的总数就是最大可相容活动数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
