---
oj: "roj"
problem_id: "1136"
title: "密码翻译"
description: "逐字符模拟加密规则：字母在大小写各自的 26 环上右移一位，z/Z 绕回，非字母原样保留。"
difficulty: "入门"
date: 2026-09-29 20:26
updated: 2026-10-05 03:07
toc: true
tags:
  - 入门
  - 字符串
  - 模拟
  - 表驱动
  - python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1136
---

[[TOC]]

## 题目描述

对给定的一个字符串加密：把其中 a-y、A-Y 的字母用其后继字母替代，把 z 和 Z 用 a 和 A 替代，其他非字母字符不变。输入一行，包含一个字符串，长度小于 80 个字符；输出加密后的字符串。

样例输入 `Hello! How are you!`，样例输出 `Ifmmp! Ipx bsf zpv!`。

## 思路

逐字符扫描：小写和大写字母各自构成一个长度为 26 的循环，右移一位即可，`z`/`Z` 单独绕回 `a`/`A`；非字母字符原样保留。注意必须整行读入，空格和标点才不会被丢掉。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
