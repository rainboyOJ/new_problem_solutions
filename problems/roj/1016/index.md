---
oj: "roj"
problem_id: "1016"
title: "整型数据类型存储空间大小"
description: "无输入题：用 sizeof(int) 与 sizeof(short) 问编译器当前平台的类型宽度，按序输出 4 2。"
difficulty: "入门"
date: 2026-09-29 13:31
updated: 2026-10-04 22:38
toc: true
tags: ["入门", "语法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1016
---

[[TOC]]

## 题目描述

分别定义 `int`、`short` 类型的变量各一个，依次输出它们的存储空间大小（单位：字节），两个整数之间用一个空格隔开。本题无输入，在本评测平台（64 位 g++）上输出 `4 2`。

## 思路

类型宽度由平台决定，不手写常数，直接用 `sizeof(int)` 和 `sizeof(short)` 问编译器即可。在常见 64 位平台上结果为 4 和 2，按题面顺序用空格分隔输出。

## 参考代码

@include-code(./main.cpp, cpp)
