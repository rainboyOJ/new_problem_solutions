---
oj: "luogu"
problem_id: "P5730"
title: "【深基5.例10】显示屏"
description: "为每个数字预存 3x5 点阵模板，按行拼接所有数字并用点列分隔。"
difficulty: "入门"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5730
---

[[TOC]]

### 题意

给出一串数字，把每个数字显示成 `3 * 5` 的点阵。数字之间用一列 `.` 隔开，最终输出 `5` 行。

### 思路

先把 `0..9` 每个数字的五行模板存起来。例如 `0` 是：

```text
XXX
X.X
X.X
X.X
XXX
```

输出时不要一个数字一个数字竖着输出，而是按行拼接：

1. 枚举点阵的第 `row` 行，`row = 0..4`；
2. 取出每个数字模板的第 `row` 行；
3. 用 `".".join(...)` 在数字之间插入一列间隔点；
4. 输出这一整行。

这题是字符串模板拼接，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题用字符串列表和 `".".join(...)` 拼接输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：读取一串数字时用 `input().strip()` 保留每个字符。
- 字典 `patterns[digit]` 可以通过字符数字找到对应模板。
- 列表推导式 `[patterns[digit][row] for digit in digits]` 收集同一行的所有数字片段。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

字典图案 + join：

@include-code(./main-pythonic.py, python)


### 复杂度

设数字位数为 `n`。一共输出 `5` 行，每行拼接 `n` 个片段，时间复杂度是 $O(n)$，模板空间为常数，输出行空间是 $O(n)$。

### 总结

显示屏题的核心是“按行拼接模板”。先把每个数字的五行写成数据，输出时只负责取模板和拼接，逻辑会很稳定。
