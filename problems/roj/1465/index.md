---
oj: "roj"
problem_id: "1465"
title: "「一本通 2.2 例 1」剪花布条"
description: "用 KMP 匹配模式串，每次匹配成功立即计数并清零匹配指针，保证子串互不重叠。"
difficulty: "普及-"
date: 2026-09-30 12:30
updated: 2026-10-06 00:19
toc: true
tags:
  - "字符串"
  - "KMP"
  - "贪心"
favorite: false
favorite_reason: ""
categories:
  - "字符串算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1465
---

[[TOC]]

## 题目描述

输入多组测试数据，每组一行，由空格分开的主串和模式串。求主串中最多能剪出多少个互不重叠的完整模式串。输入中单独一行 `#` 表示结束（字符串内部或开头的 `#` 不算结束）。

数据范围：字符串长度 ≤ 1000。

## 思路

从左到右扫描主串，用 KMP 匹配模式串；一旦完整匹配成功，答案加 1 并把匹配指针清零，确保剪出的子串互不重叠。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
