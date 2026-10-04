---
oj: "roj"
problem_id: "1040"
title: "输出绝对值"
description: "浮点数先取绝对值再用 .2f 格式化，一步完成舍入与补零；先格式化会产生 -0.00，round 又不补零。"
difficulty: "入门"
date: 2026-09-29 15:36
updated: 2026-10-04 23:13
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1040
---

[[TOC]]

## 题目描述

输入一个浮点数 $x$（$|x| \le 10000$），输出它的绝对值，保留两位小数。

样例：输入 `-3.14`，输出 `3.14`。

## 思路

先 `scanf` 读入，再用 `fabs` 取绝对值，最后用 `printf("%.2f")` 输出；必须先取绝对值再格式化，否则会出现 `-0.00`。

## 参考代码

@include-code(./main.cpp, cpp)
