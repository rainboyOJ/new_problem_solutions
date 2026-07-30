---
oj: "noi_openjudge"
problem_id: "ch0107-10"
title: "简单密码"
description: "对大写密文字母在 26 个位置上循环左移五位，保留非字母字符。"
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
source: http://noi.openjudge.cn/ch0107/10/
---

[[TOC]]

### 题意

凯撒密文将明文大写字母后移五位。给定密文，恢复明文；非字母字符不变。

### 思路

把大写字母映射到 $0$ 到 $25$。解密相当于减去 $5$，`% 26` 处理 A 前面的循环，再转回字符。非大写字母原样返回。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

循环字母表的平移可统一为“转下标、取模、转回字符”。
