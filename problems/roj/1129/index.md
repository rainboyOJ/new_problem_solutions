---
oj: "roj"
problem_id: "1129"
title: "统计数字字符个数"
description: "用 fgets 按 255 字符缓冲区整行读入，单遍扫描统计 ASCII 数字字符个数。"
difficulty: "入门"
date: 2026-09-29 20:16
updated: 2026-10-05 02:53
toc: true
tags: ["字符串", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1129
---

[[TOC]]

## 题目描述

输入一行字符串，字符集含大小写字母、数字、空格与英文标点，长度不超过 255。统计其中 `'0'` 到 `'9'` 字符的个数并输出。

## 思路

整行读入后只统计前 255 个字符，从左到右扫描，遇到 ASCII 数字字符就计数。缓冲区大小为 256 字节时实际最多保存 255 个可见字符，与官方参考实现的读取语义一致。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
