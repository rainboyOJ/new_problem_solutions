---
oj: "roj"
problem_id: "1134"
title: "合法C标识符查"
description: "首字符必须是字母或下划线，其余每个字符必须是字母、数字或下划线；满足则输出 yes，否则输出 no。"
difficulty: "入门"
date: 2026-09-29 20:26
updated: 2026-10-05 02:59
toc: true
tags: ["入门", "字符串", "条件判断"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1134
---

[[TOC]]

## 题目描述

给定一个不含空白符、长度不大于 20 的字符串，判定它是否为 C 语言的合法标识符（题面保证它不是保留字）。规则：只包含字母、数字和下划线 `_`，且不以数字开头。是则输出 `yes`，否则输出 `no`。

样例输入：`RKPEGX9R;TWyYcp`，其中第 8 位 `;` 不在合法字符集中，因此输出 `no`。

## 思路

首字符单独判定（必须是字母或下划线），其余每一位都用同一集合（字母、数字、下划线）扫一遍；任一位不通过就输出 `no`，全过则输出 `yes`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)