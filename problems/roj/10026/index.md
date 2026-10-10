---
oj: "roj"
problem_id: "10026"
title: "Clock"
description: "把时、分、秒各写成 6 位二进制排成 3×6 矩阵，按列和按行各拼接一次，输出两个 18 位串。"
difficulty: "入门"
date: 2026-10-02 19:15
updated: 2026-10-04 22:06
toc: true
tags:
  - "字符串"
  - "模拟"
  - "进制"
favorite: false
favorite_reason: ""
categories:
  - "模拟"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10026
---

[[TOC]]

## 题目描述

小 s 想把时间用二进制表示：给定 `HH:MM:SS` 形式的 24 小时制时刻，把时、分、秒各写成 6 位二进制（补零），排成 3×6 的 01 矩阵，再用两种方式读出两个 18 位串。输入一行一个 `XX:XX:XX` 时刻；输出一行两个空格隔开的串，前者竖着按列自左向右读（每列自上而下），后者横着把三行首尾相接读。样例输入 `10:37:49`，样例输出 `011001100010100011 001010100101110001`。$0 \leqslant$ 时 $\leqslant 23$，$0 \leqslant$ 分、秒 $\leqslant 59$。

## 思路

把时、分、秒分别转成 6 位二进制当作矩阵的三行，再按列和按行各拼接一次，即得两个 18 位串。6 位可表示 $0 \sim 63$，时与分秒都放得下。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
