---
oj: "roj"
problem_id: "1052"
title: "计算邮资"
description: "按重量分段计费：1000克内基本费8元，超重部分每500克向上取整加收4元，加急再加5元。"
difficulty: "入门"
date: 2026-09-29 16:21
updated: 2026-10-04 23:37
toc: true
tags:
  - 模拟
  - 分段计费
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1052
---

[[TOC]]

## 题目描述

根据邮件重量和是否加急计算邮资：1000 克及以内基本费 8 元；超过 1000 克的部分每 500 克加收 4 元，不足 500 克按 500 克计算；加急再多收 5 元。输入一行整数和一个字符 `y`/`n`，输出总邮资。

## 思路

直接按规则分段计算：超重部分用 `(e + 499) / 500` 实现按 500 克向上取整，避免浮点数；加急时再额外加 5 元。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
