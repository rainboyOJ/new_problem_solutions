---
oj: "roj"
problem_id: "1027"
title: "输出浮点数"
description: "题面四行输出就是 printf 的 %f/%.5f/%e/%g；用 printf 四个格式说明符逐行输出即可。"
difficulty: "入门"
date: 2026-09-29 14:04
updated: 2026-10-04 22:51
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1027
---

[[TOC]]

## 题目描述

读入一个双精度浮点数，分别按 `%f`（默认 6 位小数）、保留 5 位小数的 `%f`、`%e`（尾数默认 6 位小数的科学计数法）、`%g`（6 位有效数字，自动在定点与科学计数法间选择）四种格式输出，各占一行，格式须与 C `printf` 的语义逐字符一致。

**样例输入**：`12.3456789`

**样例输出**：`12.345679`、`12.34568`、`1.234568e+01`、`12.3457`，依次各占一行。

## 思路

题面四行输出就是 `printf` 的 `%f`、`%.5f`、`%e`、`%g`，直接用四个格式说明符逐行输出，舍入、补零、去尾零全部交给格式引擎。注意三个 6 的含义不同：`%f` 的 6 是小数位、`%e` 的 6 是尾数小数位、`%g` 的 6 是有效数字。样例第三行 `1.234568e+001` 是旧编译器的 3 位指数写法，标准 `printf` 与评测数据均为 2 位指数，按标准格式输出即可通过。

## 参考代码

@include-code(./main.cpp, cpp)
