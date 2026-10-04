---
oj: "roj"
problem_id: "1198"
title: "逆波兰表达式"
description: "递归下降求值前缀表达式：当前 token 为运算符时递归求左右子式，否则返回浮点值。"
difficulty: "入门"
date: 2026-09-29 23:05
updated: 2026-10-05 05:19
toc: true
tags:
  - 递归
  - 表达式求值
  - 前缀表达式
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1198"
---

[[TOC]]

## 题目描述

逆波兰表达式把运算符放在两个运算数之前，如 `+ 2 3` 表示 `2 + 3`、`* + 2 3 4` 表示 `(2 + 3) * 4`。输入一行，运算符与浮点数之间用空格分隔；输出表达式的值，保留 6 位小数。

## 思路

前缀表达式的第一个 token 是当前子树的根：若为运算符，则后面紧跟的连续两段分别是左、右子表达式，递归求值后合并；若为数字，直接返回。按顺序读入所有 token，一次递归即可得到结果。

## 参考代码

@include-code(./main.cpp, cpp)
