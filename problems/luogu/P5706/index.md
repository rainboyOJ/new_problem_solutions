---
oj: "luogu"
problem_id: "P5706"
title: "【深基2.例8】再分肥宅水"
description: "用浮点除法计算每人饮料量，并用格式化字符串保留三位小数。"
difficulty: "入门"
date: 2026-07-15 17:56
toc: true
tags: ["python", "入门", "输入输出", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5706
---

[[TOC]]

### 题意

有 $t$ 毫升饮料，平均分给 $n$ 名同学。输出每名同学能得到多少毫升，保留 $3$ 位小数；再输出一共需要多少个杯子。每名同学需要 $2$ 个杯子。

### 思路

每人得到的饮料量是 `t / n`，杯子总数是 `n * 2`。这题的关键不在计算，而在输出格式：第一行必须固定显示三位小数。

`brute.py` 不适合这题，因为直接公式就是完整解法，没有需要枚举验证的算法过程。

### Python 知识

- `input().split()` 得到两个字符串 token。
- `float(t)` 把饮料总量转成浮点数，`int(n)` 把人数转成整数。
- `f"{value:.3f}"` 表示保留小数点后 $3$ 位输出，会按常规规则四舍五入。
- 多行输出可以连续调用两次 `print()`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`float`、`int`、一行多值输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：控制浮点数小数位数和多行输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

f-string：

@include-code(./main-pythonic.py, python)


### 复杂度

只做常数次运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

浮点题先看清楚题目要求“保留几位小数”。Python 的 f-string 格式化可以直接表达这个输出要求。
