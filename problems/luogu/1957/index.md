---
oj: "luogu"
problem_id: "P1957"
title: "口算练习题"
description: "逐行解析运算类型，缺省类型时沿用上一题，再格式化表达式并输出长度。"
difficulty: "入门"
date: 2026-07-15 20:30
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1957
---

[[TOC]]

### 题意

输入若干道口算题。每行可能有三个数据，也可能有两个数据。三个数据时第一个字符表示运算类型：`a` 加法、`b` 减法、`c` 乘法；两个数据时，运算类型沿用上一题。对每道题输出完整算式和这个算式字符串的长度。

### 思路

维护一个变量 `current_operation` 表示当前运算类型。

- 如果当前行有三个 token，先更新 `current_operation`，再读取两个操作数。
- 如果当前行有两个 token，直接沿用 `current_operation`。

算出结果后，用 f-string 生成表达式，例如：

```text
64+46=110
```

表达式长度就是 `len(expression)`。

这题是按行解析和格式化输出练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：这类题要保留行结构，逐行 `input().split()` 更合适。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`split()` 按空白切分，`len(parts)` 可判断本行格式。
- 字典 `{"a": "+", "b": "-", "c": "*"}` 可以把操作类型映射到输出符号。
- f-string `f"{left}{symbol}{right}={result}"` 适合拼接带变量的算式。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

`operator` 映射四则运算，统一生成表达式：

@include-code(./main-pythonic.py, python)

### 复杂度

设题目数为 `i`，每题只处理常数个 token，时间复杂度是 $O(i)$，空间复杂度是 $O(1)$。

### 总结

当输入行格式会省略字段时，用一个变量保存上一行状态，再按 token 数区分两种格式。
