---
oj: "roj"
problem_id: "1013"
title: "温度表达转化"
description: "读入实数华氏温度，按公式 C=5×(F-32)÷9 用浮点除法算出摄氏温度，再保留 5 位小数输出。"
difficulty: "入门"
date: 2026-09-29 13:19
updated: 2026-10-04 22:30
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1013
---

[[TOC]]

## 题目描述

输入一个实数华氏温度 $F$（$F \geqslant -459.67$），按公式 $C = 5 \times (F-32) \div 9$ 计算摄氏温度并输出，精确到小数点后 5 位。输入一行一个实数，输出一行保留 5 位小数的实数。样例：输入 `41`，输出 `5.00000`。

## 思路

把题面公式直接翻译成浮点表达式 `5 * (F - 32) / 9`，用浮点除法避免整数截断。输出用 `fixed` 配 `setprecision(5)` 一步完成四舍五入与补零。

## 参考代码

@include-code(./main.cpp, cpp)
