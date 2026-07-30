---
oj: "noi_openjudge"
problem_id: "ch0107-18"
title: "验证子串"
description: "依次使用 in 判断两个字符串的包含关系，并按题目格式输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "匹配", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/18/
---

[[TOC]]

### 题意

判断两条字符串中是否有一条是另一条的子串，并按指定格式输出关系。

### 思路

`first in second` 直接判断第一串是否为第二串子串；若不成立，再检查相反方向。两个方向都不成立时输出 `No substring`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

朴素子串匹配最坏时间复杂度为 $O(nm)$，额外空间复杂度为 $O(1)$。

### 总结

Python 的 `in` 是最直观的子串存在性写法。
