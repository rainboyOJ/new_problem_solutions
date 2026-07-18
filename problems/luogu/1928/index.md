---
oj: "luogu"
problem_id: "P1928"
title: "外星密码"
description: "递归解析方括号结构，遇到 [D... ] 时先展开内部字符串，再重复 D 次拼接。"
difficulty: "普及-"
date: 2026-07-15 22:00
toc: true
tags: ["递归", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1928
---

[[TOC]]

### 题意

给定压缩字符串。形如 `[DX]` 表示把字符串 `X` 重复 `D` 次，压缩可以嵌套。输出完整解压后的字符串。

### 思路

递归解析最自然。

写函数 `parse(text, index)`，从 `index` 开始解析，直到遇到 `]` 或字符串结束，返回：

- 当前层展开后的字符串；
- 解析结束后的下标。

遇到大写字母，直接加入当前层结果。

遇到 `[`：

1. 读取后面的数字 `D`；
2. 递归解析括号内部；
3. 把内部字符串重复 `D` 次加入当前层。

### Python 知识

- `str.isupper()` 判断是否是大写字母。
- `str.isdigit()` 判断数字字符，适合读取一位或两位重复次数。
- 函数返回 `(结果字符串, 新下标)`，可以避免使用全局指针。
- 解压结果长度不超过 `20000`，字符串拼接列表 `parts` 足够稳妥。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

每个压缩字符解析一次，生成输出长度为 `L`，时间复杂度为 $O(L)$，空间复杂度为 $O(L)$。

### 总结

嵌套括号结构通常适合递归解析。关键是让函数既返回展开结果，也返回解析到哪里了。
