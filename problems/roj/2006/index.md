---
oj: "roj"
problem_id: "2006"
title: "命名那个数字"
description: "把单词按九键键盘映射成数字串，顺序扫描字典筛选出等于目标编号的单词。"
difficulty: "入门"
date: 2026-10-01 02:27
updated: 2026-10-06 09:19
toc: true
tags:
  - "模拟"
  - "字符串"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2006
---

[[TOC]]

## 题目描述

经典九键电话键盘（不含 `Q`、`Z`）：`2 ABC / 3 DEF / 4 GHI / 5 JKL / 6 MNO / 7 PRS / 8 TUV / 9 WXY`。
输入前部是字典中的大写单词（按字典序，少于 5000 个），最后一行是长度 1~12 的编号；输出所有按键映射后等于该编号的单词，每行一个，无解输出 `NONE`。
样例输入 `4734`，样例输出 `GREG`。

## 思路

字母到数字的映射是唯一的，所以不必从数字反向枚举字母，只需顺序扫描字典，把每个等长单词翻译成数字串并与编号比较。字典本身有序，输出天然按字典序。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
