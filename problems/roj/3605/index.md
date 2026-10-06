---
oj: "roj"
problem_id: "3605"
title: "[NOIP2013-普及]表达式求值"
description: "按 '+' 拆分加法项，每项内按 '*' 累积乘积，扫描中每步对 10000 取模，即得答案的后 4 位。"
difficulty: "普及-"
date: 2026-10-02 10:17
updated: 2026-10-06 15:08
toc: true
tags: ["模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3605
---

[[TOC]]

## 题目描述

给定一个只含数字、`+`、`*` 的表达式，计算其值；结果超过 4 位时只输出后 4 位（去掉前导零）。
输入一行表达式；输出一个整数。
样例：`1+1*3+4` → `8`，`1+1234567890*1` → `7891`，`1+1000000003*1` → `4`；运算符总数 ≤ 100000。

## 思路

扫描表达式，维护当前数字、当前乘法项的积与已累加答案，遇到 `+` 结算乘法项、`*` 把当前数字乘进项，每步对 10000 取模。

## 参考代码

@include-code(./main.cpp, cpp)
