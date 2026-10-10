---
oj: "roj"
problem_id: "1141"
title: "删除单词后缀"
description: "检查单词末尾是否命中 er/ly/ing 后缀，命中则删除并输出，否则原样输出。"
difficulty: "入门"
date: 2026-09-29 20:38
updated: 2026-10-05 03:21
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1141
---

[[TOC]]

## 题目描述

给定一个单词（不含空格，长度不超过 32）。若它以 `er`、`ly` 或 `ing` 结尾，则删除该后缀（保证删除后长度不为 0）；否则不操作。输出处理后的单词。

输入一行一个单词；输出一行处理后的单词。

## 思路

把三个后缀放进数组，依次比较单词末尾是否匹配，命中即用 `\0` 截断。因三个后缀末字符各不相同，最多命中一个，判断顺序不影响结果。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
