---
oj: "roj"
problem_id: "1024"
title: "保留3位小数的浮点数"
description: "用 printf(\"%.3f\", x) 一次完成四舍五入与定点输出，负号和补零都交给格式说明符。"
difficulty: "入门"
date: 2026-09-29 13:51
updated: 2026-10-04 22:43
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1024
---

[[TOC]]

## 题目描述

读入一个单精度浮点数，把它四舍五入保留 3 位小数后输出。输入只有一行一个浮点数，输出也只有一行，即保留 3 位小数的定点表示。样例输入 `12.34521`，输出 `12.345`。题面没有给出数据范围。

## 思路

用 `double` 读入这个浮点数，再用 `printf("%.3f", x)` 输出即可：`%.3f` 里的 3 就是保留 3 位小数，舍入、补零和负号都由格式说明符统一完成，不必自己乘除 $10^3$。单精度数据用双精度读取不会损失信息，因此不需要额外处理。

## 参考代码

@include-code(./main.cpp, cpp)
