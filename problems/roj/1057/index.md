---
oj: "roj"
problem_id: "1057"
title: "简单计算器"
description: "把「操作符→运算」做成 4 键分派，合法性即键是否存在；除零单独判，C++ 的 `/` 是向零取整。"
difficulty: "入门"
date: 2026-09-29 16:35
updated: 2026-10-04 23:43
toc: true
tags: ["入门", "模拟", "分派表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1057
---

[[TOC]]

## 题目描述

实现只支持 `+ - * /` 的整数计算器，读入两个整数 $a, b$ 和操作符 $\operatorname{op}$。操作符非法 → `Invalid operator!`；除法且 $b=0$ → `Divided by zero!`；否则输出 $a \operatorname{op} b$（除法按 C++ 向零取整，结果在 `int` 内）。输入一行 `a b op`，输出一行结果。样例 `1 2 +` → `3`。

## 思路

读入 $a, b, \operatorname{op}$ 后先判操作符是否合法，非法直接报 `Invalid operator!`；再判除零（仅当 `op == '/' && b == 0`），最后按 `+ - * /` 分支做对应整数运算，C++ 的 `/` 天然向零取整。

## 参考代码

@include-code(./main.cpp, cpp)