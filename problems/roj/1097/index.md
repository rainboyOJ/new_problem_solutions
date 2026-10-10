---
oj: "roj"
problem_id: "1097"
title: "画矩形"
description: "按行模板生成矩形：实心整行填充字符，空心只在首末行和左右两条边画字符。"
difficulty: "入门"
date: 2026-09-29 18:40
updated: 2026-10-05 01:01
toc: true
tags: ["模拟", "字符串", "一本通"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1097
---

[[TOC]]

## 题目描述

给定高 $h$、宽 $w$、画图字符 $c$、标志 $d$（$3 \le h \le 10$，$5 \le w \le 10$）：$d=1$ 输出 $h \times w$ 的实心 $c$ 方阵；$d=0$ 输出空心矩形（首末行、左右两列填 $c$，其余填空格）。输入一行 `h w c d`，输出画出的图形。

样例输入 `7 7 @ 0` 对应一个 7×7 的空心 `@` 矩形。

## 思路

以"行"为枚举单位：先造出 border（$c$ 重复 $w$ 次）和 middle（空心时为 $c$+$w-2$ 个空格+$c$，实心时等于 border），再拼成 `border + middle × (h-2) + border` 一次性输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
