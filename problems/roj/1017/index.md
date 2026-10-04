---
oj: "roj"
problem_id: "1017"
title: "浮点型数据类型存储空间大小"
description: "C++ 中 float 占 4 字节、double 占 8 字节，直接用 sizeof 输出即可。"
difficulty: "入门"
date: 2026-09-29 13:30
updated: 2026-10-04 22:37
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1017
---

[[TOC]]

## 题目描述

分别定义 `float`、`double` 变量各一个，输出它们占用的字节数。

输入：无；输出：一行两个整数，用一个空格隔开。

数据范围：答案恒为 4 和 8。

## 思路

直接用 `sizeof(float)` 和 `sizeof(double)` 得到字节数并输出。

## 参考代码

@include-code(./main.cpp, cpp)
