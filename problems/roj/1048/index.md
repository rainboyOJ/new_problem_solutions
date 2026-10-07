---
oj: "roj"
problem_id: "1048"
title: "有一门课不及格的学生"
description: "把两门课是否不及格当作 0/1 计数相加，和恰好为 1 时输出 1，一次覆盖四种成绩组合。"
difficulty: "入门"
date: 2026-09-29 16:09
updated: 2026-10-04 23:31
toc: true
tags: ["入门", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1048
---

[[TOC]]

## 题目描述

给出语文、数学两门成绩，判断是否恰好有一门不及格（小于 60）。是输出 1，否则输出 0。

## 思路

把两门课是否不及格当作 0/1 计数相加，和恰好为 1 时输出 1。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
