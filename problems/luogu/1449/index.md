---
oj: "luogu"
problem_id: "P1449"
title: "后缀表达式"
description: "从左到右扫描后缀表达式，数字入栈，遇到运算符就弹出两个操作数计算后再压回。"
difficulty: "普及-"
date: 2026-07-06 20:42
toc: true
tags: ["栈", "模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1449
---

[[TOC]]

### 题意

给出一个后缀表达式。表达式中：

- 数字后面用 `.` 表示这个操作数结束；
- `@` 表示整个表达式结束；
- 运算符只包含 `+ - * /`；
- 除法按 C++ 整数除法规则向 `0` 取整。

求表达式的值。

### 思路

后缀表达式的好处是：不需要考虑括号和优先级，只需要从左到右处理。

先看一个直接模拟版：

@include-code(./brute.cpp, cpp)

核心规则只有两类：

1. 读到一个完整数字，就把它压入栈；
2. 读到一个运算符，就弹出栈顶两个数，先弹出的是右操作数，后弹出的是左操作数，算完后把结果压回栈。

例如遇到 `5 2 -` 时，应计算 `5 - 2`，而不是 `2 - 5`。所以减法和除法尤其要注意左右顺序。

正式代码一边扫描字符串，一边把连续数字拼成整数；遇到 `.` 时说明数字结束，压栈；遇到运算符时完成一次计算；遇到 `@` 结束。

### Python 知识

- Python 列表的 `append/pop` 正好实现栈顶压入与弹出。
- 连续数字先收集到字符列表，遇到 `.` 后用 `int("".join(digits))` 转成整数，再 `clear()` 复用列表。
- Python 的 `//` 是向负无穷取整，不等于题目要求的向零取整；代码用绝对值整除后恢复符号。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串逐字符扫描与拼接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：频繁字符串拼接应先收集再 `join`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

- 时间复杂度：$O(|s|)$
- 空间复杂度：$O(|s|)$

### 总结

后缀表达式求值是栈的经典应用。看到数字入栈，看到运算符弹两个数计算，再把结果压回去。
