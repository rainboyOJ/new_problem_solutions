---
oj: "roj"
problem_id: "1023"
title: "Hello,World!的大小"
description: "C 字符串字面量末尾隐含 '\\0'，sizeof(\"Hello, World!\") = 13 + 1 = 14。"
difficulty: "入门"
date: 2026-09-29 13:52
updated: 2026-10-04 22:44
toc: true
tags: ["输入输出", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1023
---

[[TOC]]

## 题目描述

题目问 C 字符串字面量 `"Hello, World!"` 占多少字节。

输入：无。

输出：一个整数，即该字面量的大小。

样例：无输入，输出 `14`。

数据范围：答案固定为 14。

## 思路

C 的字符串字面量在末尾自动追加 `'\0'`，因此 `sizeof("Hello, World!")` = 13（可见字符）+ 1（结束符）= 14，直接打印即可。

## 参考代码

@include-code(./main.cpp, cpp)
