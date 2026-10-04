---
oj: "roj"
problem_id: "1004"
title: "字符三角形"
description: "给定字符按 3 行输出等腰三角形：第 row 行补 2-row 个左空格、重复 2*row+1 个字符，公式化居中且不留行尾空格。"
difficulty: "入门"
date: 2026-09-29 12:32
updated: 2026-10-04 22:15
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1004
---

[[TOC]]

## 题目描述

给定一个字符 `c`，输出底边长 5、高 3 的等腰三角形。输入一行一个字符；第 `i` 行（`i=0,1,2`）左补 `2-i` 个空格、再写 `2*i+1` 个 `c`，行尾不留多余空格。样例：`*` → `  *` / ` ***` / `*****` 三行。

## 思路

对 `row = 0,1,2` 用两个等差公式直接打：左补 `2-row` 个空格 + `2*row+1` 个字符 `c`，逐行输出即可。

## 参考代码

@include-code(./main.cpp, cpp)