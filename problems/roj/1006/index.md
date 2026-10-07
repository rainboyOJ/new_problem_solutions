---
oj: "roj"
problem_id: "1006"
title: "正负数"
description: "把题面定义“负数就是在正数前加负号”当词法规则：token 首字符为 - 则原样输出，否则前补负号，字符串分派避免 float 往返破坏书写格式。"
difficulty: "入门"
date: 2026-09-29 12:44
updated: 2026-10-04 22:22
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1006
---

[[TOC]]

## 题目描述

小叶子刚学会了负数，她觉得很有意思：负数就是在正数前加负号（`-`）。她决定写个程序，不管输入是正数还是负数，输出结果都为负数。例如：输入 `1`，输出 `-1`；输入 `-1.5`，输出 `-1.5`。

输入文件中只有一个不为 0 的数（可能以 `-` 开头，可能含小数点）；输出文件中只有一个负数，且数字部分要和输入逐字符相同（小数位、尾随零原样保留）。

## 思路

题面要的是“负数形式的原样书写”，这是书写形式操作而不是数值运算：把输入读成一个字符串，首字符是 `-` 就原样输出，否则在最前面补一个 `-`。千万不要用 `float` 读入再取负——往返会丢掉尾随零，大数还会变成科学计数法。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
