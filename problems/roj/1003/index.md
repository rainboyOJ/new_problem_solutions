---
oj: "roj"
problem_id: "1003"
title: "对齐输出"
description: "用 printf 的 %8lld 把三个整数按最小宽度 8 右对齐输出，字段之间以一个空格分隔。"
difficulty: "入门"
date: 2026-09-29 11:15
updated: 2026-10-04 22:16
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1003
---

[[TOC]]

## 题目描述

读入三个整数，每个整数按最小宽度 8 右对齐输出，字段间以一个空格分开。输入一行三个整数，输出一行按要求输出。样例输入 `123456789 0 -1`，样例输出 `123456789        0       -1`。

## 思路

`printf` 的 `%8lld` 天然是最小宽度 8 的右对齐字段；两个 `%8lld` 之间的空格作为字段分隔。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
