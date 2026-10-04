---
oj: "roj"
problem_id: "1138"
title: "将字符串中的小写字母转换成大写字母"
description: "整行读入后逐字符扫描，把小写字母减 32 转大写，其余字符（含空格、数字、已有大写）原样输出。"
difficulty: "入门"
date: 2026-09-29 20:25
updated: 2026-10-05 03:07
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1138
---

[[TOC]]

## 题目描述

给定一个字符串（长度不超过 100，可能包含空格），把其中所有小写字母转成大写，其余字符原样保留。输入一行字符串，输出转换后的结果。样例输入：`helloworld123Ha`；样例输出：`HELLOWORLD123HA`。

## 思路

整行读入后逐字符扫描，遇到小写字母减 32 转大写，其余原样输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
