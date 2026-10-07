---
oj: "roj"
problem_id: "1160"
title: "倒序数"
description: "把 n 的十进制表示整串反转后按字符串输出，反转后开头出现的 0 要原样保留。"
difficulty: "入门"
date: 2026-09-29 21:25
updated: 2026-10-05 03:58
toc: true
tags: ["python", "字符串", "递归", "输入输出"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1160
---

[[TOC]]

## 题目描述

输入一个非负整数（保证个位不为零），输出这个数的倒序数：把十进制表示整串反转后输出，反转后开头出现的 `0` 要原样保留。例如输入 `123`，输出 `321`。

## 思路

读入 n 的十进制表示存成字符串，从最后一个字符往前逐个输出就是倒序数。关键点是答案按数字串处理而不是数值：像 `1234567890` 这样末尾有 0 的输入，反转后开头的 `0` 必须原样打印，所以反转结果绝不能再转回整数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
