---
oj: "roj"
problem_id: "1001"
title: "Hello,World!"
description: "无输入的常量输出题：直接输出字符串 Hello,World!，注意逗号后和感叹号前都没有空格。"
difficulty: "入门"
date: 2026-09-29 11:09
updated: 2026-10-04 22:05
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1001
---
[[TOC]]

## 题目描述
编写一个能够输出 `Hello,World!` 的程序，用来测试开发、编译环境能否正常工作。提示：`Hello,World!` 中间没有空格。
输入：无。输出：一行 `Hello,World!`。
输入样例：`（无）`，输出样例：
```
Hello,World!
```

## 思路
本题没有输入、没有计算，直接把字符串 `Hello,World!` 输出即可。唯一要小心标点：`Hello` 和 `World` 之间只有一个英文逗号且逗号后无空格，`World` 后紧跟英文感叹号。`cout` 输出字符串后再输出 `endl` 补上换行，与评测数据逐字节一致。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
