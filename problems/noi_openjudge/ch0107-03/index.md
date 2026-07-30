---
oj: "noi_openjudge"
problem_id: "ch0107-03"
title: "基因相关性"
description: "逐位置比较两条 DNA 序列，计算相同碱基对比例并与阈值比较。"
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
source: http://noi.openjudge.cn/ch0107/03/
---

[[TOC]]

### 题意

两条等长 DNA 序列中，相同位置碱基对的比例不低于阈值时输出 `yes`。

### 思路

`zip(first, second)` 配对相同位置字符，累加相等判断，除以序列长度得到比例。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，除输入字符串外额外空间复杂度为 $O(1)$。

### 总结

等长序列的逐位置比较可直接用 `zip` 表达。
