---
oj: "luogu"
problem_id: "P5733"
title: "【深基6.例1】自动修正"
description: "直接使用字符串的 upper 方法，把所有小写字母转换成大写后输出。"
difficulty: "入门"
date: 2026-07-15 20:30
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5733
---

[[TOC]]

### 题意

输入一个长度不超过 `100`、不含空格的字符串。把其中所有小写字母改成大写字母，其他字符保持不变。

### 思路

Python 字符串自带 `upper()` 方法，它会把英文字母转成大写，数字、标点等非小写字母不会受到影响。

这题的重点是认识字符串方法，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`input()` 读取不含空格的一行字符串。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：不含空格的字符串直接用 `s = input()`。
- `s.upper()` 返回一个新字符串，原字符串不会被原地修改。

### 代码

@include-code(./main.py, python)

### 复杂度

设字符串长度为 `n`，时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

遇到整串大小写转换时，优先使用 Python 字符串方法，比手动逐个字符判断更清楚。
