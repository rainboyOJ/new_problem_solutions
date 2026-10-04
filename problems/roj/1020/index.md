---
oj: "roj"
problem_id: "1020"
title: "打印ASCII码"
description: "读入一个可见字符，用 %c 读入后利用 char 的整型提升直接输出其 ASCII 码，O(1) 完成"
difficulty: "入门"
date: 2026-09-29 13:42
updated: 2026-10-04 22:38
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1020
---

[[TOC]]

## 题目描述

输入一个除空格以外的可见字符，输出它的 ASCII 码。

- **输入**：一个除空格以外的可见字符。
- **输出**：一个十进制整数，即该字符的 ASCII 码。

样例输入 `A`，输出 `65`。

## 思路

用 `%c` 读入单个字符到 `char` 变量，输出时 `char` 会整型提升为 `int`，其值恰好是该字符的 ASCII 码，直接 `printf("%d")` 即可，整个过程 O(1)。

## 参考代码

@include-code(./main.cpp, cpp)
