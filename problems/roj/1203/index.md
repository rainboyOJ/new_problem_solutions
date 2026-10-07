---
oj: "roj"
problem_id: "1203"
title: "扩号匹配问题"
description: "多组括号匹配：一趟从左到右扫描，栈存未配对左括号下标；遇栈空右括号标 ?，扫描后残留左括号标 $，线性时间。"
difficulty: "入门"
date: 2026-09-29 23:28
updated: 2026-10-05 05:27
toc: true
tags:
  - 字符串
  - 栈
  - 模拟
  - python
favorite: false
favorite_reason: ""
categories:
  - 字符串
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1203
---

[[TOC]]

## 题目描述
多组数据读到 EOF，每行只含 `(`、`)` 与大小写字母，长度不超过 $100$。每个 `(` 与它右边距离最近的 `)` 配对（从内到外）。对每行输出两行：第一行原串，第二行等长标注——多余的 `(` 标 `$`，多余的 `)` 标 `?`，其余位置留空格。样例见 `problem.md`。

## 思路
从左到右扫一遍，用栈存尚未配对的左括号下标：读到 `(` 入栈，读到 `)` 时栈非空则弹栈配对、栈空则该 `)` 标 `?`；扫描结束后栈里剩下的左括号全部标 `$`。每字符最多入/出栈一次，时间 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
