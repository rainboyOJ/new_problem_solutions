---
oj: "roj"
problem_id: "10000"
title: "牛牛的密码"
description: "一次扫描把字符按 ASCII 区间分入四个桶，append 顺序天然保序，等级为非空桶数。"
difficulty: "入门"
date: 2026-10-02 17:17
updated: 2026-10-04 21:36
toc: true
tags: ["入门", "字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10000
---

[[TOC]]

## 题目描述

给定非空字符串 $s$。把字符按四类拆出并保留原相对顺序：小写 `a-z`、大写 `A-Z`、数字 `0-9`、其余特殊字符。输出 `password level:X`（$X$ 为非空部分数），再按上述顺序输出四部分，空串输出 `(Null)`。

## 思路

一次扫描字符串，按 ASCII 区间把每个字符 push 进对应桶，桶内顺序即原串相对顺序。扫描结束后统计非空桶数得到等级，再逐桶输出，空桶替换为 `(Null)`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
