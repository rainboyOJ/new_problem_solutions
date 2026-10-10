---
oj: "roj"
problem_id: "20001"
title: "数字绕口令"
description: "把数字串反转后删去前导 0 输出，字符串反转即可，无需任何算术运算。"
difficulty: "入门"
date: 2026-10-02 19:16
updated: 2026-10-06 02:11
toc: true
tags: ["入门", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20001
---

[[TOC]]

## 题目描述

给定一个长度不超过 250 的数字串，把这个数字的数位顺序整体颠倒后输出，且结果的开头不能为 0（结果为 0 时输出 `0`）。

## 思路

把字符串反转后输出即可：反转后开头的 0 恰好对应原串末尾的 0，删去这些前导 0（其余位置的 0 不动）；全 0 输入删成空串时输出 `0`。数字串长达 250 位，装不进 64 位整数，但这题的"倒序"只是换位置，不产生进位借位，纯字符串操作就能完成。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
