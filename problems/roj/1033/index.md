---
oj: "roj"
problem_id: "1033"
title: "计算线段长度"
description: "读入两端点坐标，按勾股定理求线段长度并保留 3 位小数。"
difficulty: "入门"
date: 2026-09-29 15:03
updated: 2026-10-04 23:00
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1033
---

[[TOC]]

## 题目描述

已知线段两端点 $A(X_a,Y_a)$、$B(X_b,Y_b)$，求 $AB$ 的长度并保留到小数点后 3 位。第一行 $X_a,Y_a$，第二行 $X_b,Y_b$，坐标绝对值 $\le 10000$。样例输入：`1 1\n2 2`；样例输出：`1.414`。

## 思路

按勾股定理 $\sqrt{(X_a-X_b)^2+(Y_a-Y_b)^2}$ 直译；输出用 `%.3f` 一次完成四舍五入与补零。

## 参考代码

@include-code(./main.cpp, cpp)
