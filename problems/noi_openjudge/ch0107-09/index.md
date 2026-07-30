---
oj: "noi_openjudge"
problem_id: "ch0107-09"
title: "密码翻译"
description: "逐字符将英文字母后移一位，并分别处理小写与大写字母的循环边界。"
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
source: http://noi.openjudge.cn/ch0107/09/
---

[[TOC]]

### 题意

将字母替换为字母表后继，`z` 循环到 `a`，`Z` 循环到 `A`，其他字符不变。

### 思路

普通字母可用 ASCII 码加一；`z`、`Z` 是循环边界，要单独映射。生成器逐字符调用 `encrypt` 后拼接输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

字符平移题最重要的边界是字母表末尾的回绕。
