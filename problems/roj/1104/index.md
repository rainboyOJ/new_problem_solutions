---
oj: "roj"
problem_id: "1104"
title: "计算书费"
description: "把单价放大 10 倍转成整数角，读入 10 个数量后做整数加权和，最后除以 10 输出一位小数。"
difficulty: "入门"
date: 2026-09-29 19:35
updated: 2026-10-05 01:15
toc: true
tags: ["入门", "数学", "模拟", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1104
---

[[TOC]]

## 题目描述

输入 10 个整数，依次表示 10 种图书的购买数量；输出应付总费用，精确到小数点后一位。

## 思路

十种图书单价都是一位小数，把单价表放大 10 倍变成以「角」为单位的整数，读入数量后逐项做整数乘积并累加，最后把总和除以 10 按一位小数输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
