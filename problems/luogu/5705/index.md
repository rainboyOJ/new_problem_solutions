---
oj: "luogu"
problem_id: "P5705"
title: "【深基2.例7】数字反转"
description: "把输入当作字符串处理，用切片反转后输出。"
difficulty: "入门"
date: 2026-07-15 17:50
toc: true
tags: ["python", "入门", "字符串", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5705
---

[[TOC]]

### 题意

输入一个形如 `123.4` 的一位小数，要求把所有字符倒过来，输出 `4.321`。

### 思路

虽然题面说这是浮点数，但真正要做的是“字符顺序反转”。如果先转成 `float`，可能引入不必要的格式问题；直接把输入当字符串处理最简单。

`brute.py` 不适合这题，因为没有算法优化过程；字符串切片反转就是完整解法。

### Python 知识

- `input()` 读取一行文本，得到字符串。
- `s[::-1]` 是切片写法，表示从后往前取完整字符串。
- 题目要求保留小数点的位置随字符一起反转，所以不能把输入转成数字再处理。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串下标、切片和反转。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：读取字符串输入。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

切片反转：

@include-code(./main-pythonic.py, python)


### 复杂度

字符串长度固定很小，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

看到“数字反转”不要急着转成数值类型。只要题目关心的是字符格式，Python 字符串切片通常更直接、更稳。
