---
oj: "roj"
problem_id: "1178"
title: "成绩排序"
description: "把学生按成绩降序排序，同分时按姓名字典序升序输出。"
difficulty: "入门"
date: 2026-09-29 22:16
updated: 2026-10-05 04:26
toc: true
tags:
  - 排序
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1178"
---

[[TOC]]

## 题目描述

给出班里 $n$（$0<n<20$）个学生的姓名与成绩，成绩为 $[0,100]$ 的整数，按成绩从高到低输出，同分时姓名字典序小的在前，每行 `名字 成绩`。样例：输入 `4 / Kitty 80 / Hanmeimei 90 / Joey 92 / Tim 28`，输出 `Joey 92 / Hanmeimei 90 / Kitty 80 / Tim 28`。

## 思路

存 `(name, score)`，自定义比较：成绩降序，同分则名字字典序升序，`sort` 一遍后按序输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)