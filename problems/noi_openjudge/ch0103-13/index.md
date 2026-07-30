---
oj: "noi_openjudge"
problem_id: "ch0103-13"
title: "反向输出一个三位数"
description: "把三位输入按字符串反转，保留反转后的前导零。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/13/
---

[[TOC]]

### 题意

反向输出一个三位数，例如 `100` 必须输出 `001`。

### 思路

把输入保留为字符串而非转为整数，使用切片 `number[::-1]` 反转。这样反转得到的 `001` 不会在再次转换为整数时丢失前导零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

字符串长度固定为 3，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

当输出格式需要保留前导零时，把数字当字符串处理通常比拆位更直接。
