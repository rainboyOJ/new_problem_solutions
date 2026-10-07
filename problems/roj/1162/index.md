---
oj: "roj"
problem_id: "1162"
title: "字符串逆序"
description: "读取以 '!' 结尾的字符串，把 '!' 之前的部分逆序输出。"
difficulty: "入门"
date: 2026-09-29 21:25
updated: 2026-10-05 03:57
toc: true
tags: ["字符串", "入门", "字符串反转"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1162
---

[[TOC]]

## 题目描述

输入一串以 `'!'` 结尾的字符序列，把 `'!'` 之前的部分按逆序输出。输入一行字符（以 `'!'` 结尾）；样例输入 `abc!` 对应样例输出 `cba`。

## 思路

把整行读到字符数组里，定位终止符 `'!'`，从后往前逐个输出它前面的字符即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)