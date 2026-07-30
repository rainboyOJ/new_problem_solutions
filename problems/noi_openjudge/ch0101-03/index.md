---
oj: "noi_openjudge"
problem_id: "ch0101-03"
title: "对齐输出"
description: "用 f-string 的右对齐宽度 8 格式化三个整数，再以空格分隔输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/03/
---

[[TOC]]

### 题意

读入三个整数。每个整数都要在至少宽 8 个字符的位置中右对齐，相邻两个位置之间再输出一个空格。

如果整数本身已经超过 8 个字符，宽度只是最小宽度，不能截断它。

### 思路

Python 的格式说明 `:>8` 表示右对齐、最小宽度为 8。因此 `f"{number:>8}"` 就对应 C++ 的 `setw(8)`。

三个格式化后的字符串交给 `print` 并用默认分隔符输出，默认的一个空格正好是题目要求的字段间空格。生成器逐个产生格式化结果，不必先建立列表。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

只处理三个固定整数，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

记住 `f"{x:>8}"`：`>` 表示右对齐，`8` 表示最小字段宽度。格式控制不会截断较长的整数。
