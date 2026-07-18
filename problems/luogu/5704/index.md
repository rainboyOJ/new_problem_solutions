---
oj: "luogu"
problem_id: "P5704"
title: "【深基2.例6】字母转换"
description: "读入一个小写字母，使用字符串 upper 方法转换成大写。"
difficulty: "入门"
date: 2026-07-15 17:50
toc: true
tags: ["python", "入门", "字符串", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5704
---

[[TOC]]

### 题意

输入一个小写字母，输出对应的大写字母。

### 思路

Python 字符串自带大小写转换方法。题目保证输入是一个小写字母，所以直接读入字符串并调用 `upper()`。

`brute.py` 不适合这题，因为最终做法就是标准库字符串方法，没有需要对拍的算法分支。

### Python 知识

- `input()` 读取一行字符串，并去掉末尾换行。
- `letter.upper()` 返回转换后的新字符串，不会原地修改 `letter`。
- 对单个字符和普通字符串都可以调用 `upper()`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：读取字符串与常用字符串操作。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：读取一个不含空格字符串。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

str.upper：

@include-code(./main-pythonic.py, python)

### 复杂度

输入长度固定为 $1$，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

字符串题先想清楚输入是“一个 token”还是“整行文本”。本题只有一个小写字母，用 `input()` 和 `upper()` 就足够。
