---
oj: "noi_openjudge"
problem_id: "ch0104-19"
title: "简单计算器"
description: "按运算符分支计算，并优先处理除零和非法运算符。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/19/
---

[[TOC]]

### 题意

实现支持 `+`、`-`、`*`、`/` 的整数计算器；除零和非法运算符有指定提示。

### 思路

按运算符逐个分支。除法分支先检查零除数；商使用向零截断辅助函数，以匹配 C/C++ 整数除法而不是 Python 负数 `//` 规则。未知运算符走最后的错误分支。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

分支数固定，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

模拟题先列举输入状态，再把异常状态放进独立分支，能避免非法输入落入普通计算。
