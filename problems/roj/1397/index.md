---
oj: "roj"
problem_id: "1397"
title: "简单算术表达式求值"
description: "整行恰好一个运算符，逐字符扫描定位后切成三段，按运算符做对应整数运算。"
difficulty: "入门"
date: 2026-09-30 08:34
updated: 2026-10-05 12:44
toc: true
tags: ["模拟", "字符串"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1397
---

[[TOC]]

## 题目描述

输入一行算术表达式，格式为「运算数 运算符 运算数」，运算符是 `+ - * / %` 之一，前后可能有空格，`/` 为整数整除。输出运算的整数结果。

样例输入：`32+64`，样例输出：`96`。

## 思路

整行只有一个运算符，逐字符扫描定位它，把字符串切成左运算数、运算符、右运算数三段，再按运算符做对应运算即可。

## 参考代码

@include-code(./main.cpp, cpp)
