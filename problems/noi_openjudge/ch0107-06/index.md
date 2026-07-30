---
oj: "noi_openjudge"
problem_id: "ch0107-06"
title: "合法 C 标识符"
description: "检查首字符非数字且所有字符为字母、数字或下划线，判断 C 标识符合法性。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/06/
---

[[TOC]]

### 题意

判断非保留字字符串是否是合法 C 标识符。

### 思路

首字符不能是数字；所有字符必须满足 `isalnum()` 或为下划线。两个条件同时成立才输出 `yes`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

标识符判定可拆成“首字符规则”和“全体字符规则”。
