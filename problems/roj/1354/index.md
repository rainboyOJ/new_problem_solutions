---
oj: "roj"
problem_id: "1354"
title: "括弧匹配检验"
description: "用一个栈存尚未闭合的左括号：右括号只能配栈顶的同类左括号，扫描结束后栈空才输出 OK，否则 Wrong"
difficulty: "入门"
date: 2026-09-30 06:50
updated: 2026-10-05 11:24
toc: true
tags: ["字符串", "栈"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1354
---

[[TOC]]

## 题目描述

给定一个只含圆括号 `( )` 与方括号 `[ ]` 的表达式，判断字符串里的括号是否匹配：每个右括号要在左边找到尚未使用且类型相同的左括号配对，配对区间不能交叉。匹配输出 `OK`，不匹配输出 `Wrong`。

输入仅一行字符串，字符个数小于 255；输出 `OK` 或 `Wrong`。样例输入 `［（］）`，样例输出 `Wrong`（样例用的是全角括号，与半角 `()[]` 等价）。

## 思路

用栈保存尚未闭合的左括号，它们从外到内依次入栈。遇左括号入栈；遇右括号时，只有栈非空且栈顶正好是它的同类左括号才能弹出配对，否则立即判 `Wrong`；扫描结束后栈为空才算 `OK`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
