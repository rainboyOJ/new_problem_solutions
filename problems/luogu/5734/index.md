---
oj: "luogu"
problem_id: "P5734"
title: "【深基6.例6】文字处理软件"
description: "用字符串切片实现追加、截取、插入和 find 查找四种文字处理操作。"
difficulty: "入门"
date: 2026-07-15 20:35
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5734
---

[[TOC]]

### 题意

维护一个文档字符串，依次执行 `q` 次操作：追加、截取、插入、查找。每次操作都要输出对应结果。

### 思路

四种操作都可以直接对应到 Python 字符串操作：

- `1 str`：`document += str`
- `2 a b`：`document = document[a:a+b]`
- `3 a str`：`document[:a] + str + document[a:]`
- `4 str`：`document.find(str)`

数据范围很小，字符串每次新建也能通过。这题是字符串 API 和切片练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片和 `find` 属于常用字符串操作。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：逐行读取操作，保留每行结构。
- `s[l:r]` 取左闭右开区间。
- `find` 找不到时返回 `-1`，正好符合题目要求。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`match-case` 分发文本操作：

@include-code(./main-pythonic.py, python)

### 复杂度

设当前文档长度为 `L`，每次字符串修改或查找最坏为 $O(L)$。`q <= 100` 且初始长度很小，可以直接模拟。

### 总结

文字处理题先把每种指令翻译成一种字符串操作，再注意切片下标是左闭右开。
