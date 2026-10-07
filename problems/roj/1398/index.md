---
oj: "roj"
problem_id: "1398"
title: "短信计费"
description: "每条短信限 70 字，每次发送占 ceil(字数/70) 条，把总条数整数累加后除以 10 换成元，保留一位小数输出。"
difficulty: "入门"
date: 2026-09-30 08:35
updated: 2026-10-05 12:44
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1398
---

[[TOC]]

## 题目描述

一条短信最多 70 字（含），每条资费 0.1 元，超过 70 字就按每 70 字一条拆成多条发送。输入第一行是当月发送次数 $n$，接着 $n$ 行每行一个整数表示该次发送的字数；输出当月总资费，精确到小数点后 1 位。样例：输入 `10` 后跟 `39 49 42 61 44 147 42 72 35 46`，输出 `1.3`。

## 思路

每次发送占 $\lceil a_i/70 \rceil$ 条短信，用整数式 $(a_i+69)/70$ 直接算条数，不必循环扣 70。把条数整数累加可避免浮点误差，最后除以 10 换成元，用 `printf("%.1f")` 输出一位小数即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
