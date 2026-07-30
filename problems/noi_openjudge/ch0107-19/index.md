---
oj: "noi_openjudge"
problem_id: "ch0107-19"
title: "字符串移位包含问题"
description: "将较长串与自身拼接，用子串判断覆盖全部循环移位后的情况。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "匹配", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/19/
---

[[TOC]]

### 题意

判断两串中是否有一串是另一串循环移位若干次后得到的字符串的子串。

### 思路

选较长串为 `longer`，较短串为 `shorter`。所有 `longer` 的循环移位都能作为 `longer + longer` 中长度与原串相同的连续片段出现，因此只需判断 `shorter in longer + longer`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设较长串与较短串长度为 $n,m$，朴素匹配最坏时间复杂度为 $O(nm)$，额外空间为 $O(n)$。

### 总结

循环移位问题常可通过“原串拼接自身”转化为普通子串问题。
