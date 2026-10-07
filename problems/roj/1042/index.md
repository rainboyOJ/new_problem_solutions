---
oj: "roj"
problem_id: "1042"
title: "奇偶ASCII值判断"
description: "读入一个字符，char 参与运算时提升为 int 得到的数值就是它的 ASCII 码，判断其奇偶输出 YES 或 NO。"
difficulty: "入门"
date: 2026-09-29 15:47
updated: 2026-10-04 23:13
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1042
---

[[TOC]]

## 题目描述

任意输入一个可见字符，判断它的 ASCII 值是否为奇数：是则输出 `YES`，否则输出 `NO`。输入一行一个字符，输出 `YES` 或 `NO`。样例：输入 `A`（ASCII 65）输出 `YES`，输入 `B`（ASCII 66）输出 `NO`。

## 思路

`char` 是整数类型，参与算术时会自动提升为 `int`，其数值正是该字符的 ASCII 码。于是直接用 `ch % 2` 判断奇偶：余 1 输出 `YES`，否则输出 `NO`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
