---
oj: "roj"
problem_id: "1026"
title: "空格分隔输出"
description: "四个 token 按各自类型读入并空格分隔输出：第 3 个数是单精度，必须存进 float，数值到 10^5 量级时 6 位小数才与参考解一致。"
difficulty: "入门"
date: 2026-09-29 14:04
updated: 2026-10-04 22:44
toc: true
tags: ["入门", "输入输出", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1026
---

[[TOC]]

## 题目描述

读入一个字符、一个整数、一个单精度浮点数、一个双精度浮点数（输入共四行，依次为这四个值），然后按顺序输出它们，之间用一个空格分隔；输出浮点数时保留 6 位小数。

样例：输入四行 `a` / `12` / `2.3` / `3.2`，输出 `a 12 2.300000 3.200000`。

## 思路

四个 token 各自按类型读入：字符用 `char`、整数用 `int`，第 3 个数必须用 `float`（单精度）存，第 4 个数用 `double` 存。输出用 `%.6f` 定点格式一次完成四舍五入与补零；当数值量级到 $10^5$ 时 binary32 的舍入间距超过 $10^{-6}$，用 `double` 读第 3 个数会让第 6 位小数出错。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
