---
oj: "roj"
problem_id: "1466"
title: "「一本通 2.2 例 2」Power Strings"
description: "用 KMP 失败函数求最长 border，最小正周期 p = n - pi[n-1]；p 整除 n 时答案为 n/p，否则为 1。"
difficulty: "普及"
date: 2026-09-30 12:33
updated: 2026-10-06 00:18
toc: true
tags:
  - 字符串
  - KMP
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1466
---

[[TOC]]

## 题目描述

给定若干个仅含英文字母的字符串（以单独一行 `.` 结束输入），对每个字符串求最大重数 $k$，使其能由某个子串重复 $k$ 次连接而成。字符串长度 $\le 10^6$。

## 思路

KMP 求失败函数得到最长 border 长度 $b$，最小正周期 $p = n - b$。若 $p \mid n$ 则答案为 $n/p$，否则为 $1$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
