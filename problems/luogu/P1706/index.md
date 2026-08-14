---
oj: "luogu"
problem_id: "P1706"
title: "全排列问题"
description: "使用 itertools.permutations 按字典序生成 1 到 n 的全排列，并用格式化字符串控制 5 个字符宽度。"
difficulty: "入门"
date: 2026-07-15 21:40
toc: true
tags: ["枚举", "全排列", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1706
---

[[TOC]]

### 题意

输入 `n`，按字典序输出 `1..n` 的所有排列。每个数字占 `5` 个字符宽度。

### 思路

题目要求的是完整全排列，并且 `n <= 9`。Python 标准库 `itertools.permutations` 会按照输入序列的顺序生成所有排列。

所以只需要：

1. 构造序列 `1..n`；
2. 枚举所有排列；
3. 按题目要求格式化输出。

### Python 知识

- `permutations(range(1, n + 1))` 生成 `1..n` 的所有排列。
- `f"{number:5d}"` 表示整数右对齐，占 `5` 个字符宽度。
- `"".join(...)` 把一行中的多个格式化字段拼成字符串。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### 复杂度

一共有 $n!$ 个排列，每行输出 `n` 个数，时间复杂度为 $O(n\cdot n!)$，空间复杂度为 $O(n)$。

### 总结

全排列输出题很适合用 `itertools.permutations` 学习 Python 枚举工具。它直接表达“枚举所有顺序”。
