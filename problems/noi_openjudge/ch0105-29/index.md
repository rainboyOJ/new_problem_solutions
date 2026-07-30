---
oj: "noi_openjudge"
problem_id: "ch0105-29"
title: "数字反转"
description: "分离符号后反转绝对值的数字串，并删除反转结果前端的零。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "数位", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/29/
---

[[TOC]]

### 题意

反转一个整数的十进制数位。负数的负号保留在最前面；反转后最高位不能是零。

### 思路

先记录原数是否为负数，再对绝对值的数字字符串切片 `[::-1]`，得到反转后的数位顺序。

原数末尾的零会在反转后出现在开头，`lstrip("0")` 可以删除它们。若原数为 $0$，删除后会得到空字符串，因此用 `or "0"` 恢复为合法的零。最后再把原先的负号拼回去。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设整数有 $d$ 位，时间复杂度为 $O(d)$，字符串操作使用 $O(d)$ 额外空间。

### 总结

数字反转可拆为“符号”和“绝对值数位”两部分处理，能自然覆盖负数与末尾零。
