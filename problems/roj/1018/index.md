---
oj: "roj"
problem_id: "1018"
title: "其他数据类型存储空间大小"
description: "用 sizeof 直接测量 bool 与 char 的类型宽度并按顺序输出，而不是把答案 1 1 当魔法数字硬编码"
difficulty: "入门"
date: 2026-09-29 13:31
updated: 2026-10-04 22:38
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1018
---

[[TOC]]

## 题目描述

分别定义 `bool`、`char` 类型的变量各一个，输出它们的存储空间大小（单位：字节）。本题无输入，输出一行两个整数并用一个空格隔开，依次为 `bool` 与 `char` 的大小；原题没有样例。

## 思路

题面问的是类型宽度而不是对象大小，所以直接对类型求 `sizeof`：`char` 按定义恰为 1 字节，`bool` 在常见编译器下同样占 1 字节。本题无输入，按先 `bool` 后 `char` 的顺序输出两个整数即可。

## 参考代码

@include-code(./main.cpp, cpp)
