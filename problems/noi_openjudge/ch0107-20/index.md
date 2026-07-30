---
oj: "noi_openjudge"
problem_id: "ch0107-20"
title: "删除单词后缀"
description: "依次检查 er、ly、ing 后缀，匹配时用切片删除该后缀。"
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
source: http://noi.openjudge.cn/ch0107/20/
---

[[TOC]]

### 题意

若单词以 `er`、`ly` 或 `ing` 结尾，则删除该后缀；否则原样输出。

### 思路

依次调用 `endswith` 检查候选后缀。命中后用 `word[:-len(suffix)]` 保留前缀并停止，不会重复删除多个后缀。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，输出字符串使用 $O(n)$ 空间。

### 总结

固定后缀集合的判断可用 `endswith` 配合切片清晰实现。
