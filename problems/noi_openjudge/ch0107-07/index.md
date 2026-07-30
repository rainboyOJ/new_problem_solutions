---
oj: "noi_openjudge"
problem_id: "ch0107-07"
title: "配对碱基链"
description: "建立 A-T、G-C 的互补映射，再 translate 得到配对碱基链。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "映射", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/07/
---

[[TOC]]

### 题意

输出 DNA 单链的互补碱基链，其中 A 与 T 配对，G 与 C 配对。

### 思路

用 `str.maketrans` 建立四个字符的替换表，`translate` 一次转换整条链。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

固定的一对一字符替换可用翻译表清楚表示。
