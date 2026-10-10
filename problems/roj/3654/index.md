---
oj: "roj"
problem_id: "3654"
title: "[noip2018-普及] 标题统计"
description: "一次 read() 读完整份输入，sum(生成器) 逐字符统计非空格、非换行的字符，一遍扫描即达到 Ω(|s|) 输入下界的最优。"
difficulty: "入门"
date: 2026-10-02 13:31
updated: 2026-10-06 16:00
toc: true
tags: ["python", "字符串", "输入输出"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3654
---

[[TOC]]

## 题目描述

给定字符串 $s$（大小写字母、数字、空格、换行符组成），统计其中**不为空格、不为换行符**的字符个数。输入一行字符串 $s$，输出有效字符数。样例：`Ca 45` → `4`。

## 思路

遍历每个字符，非空格且非换行则计数，输出计数器。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
