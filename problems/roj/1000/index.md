---
oj: "roj"
problem_id: "1000"
title: "A+B问题"
description: "读入两个整数直接相加输出：一行输入两个整数，用 ll 读入后输出 a+b。"
difficulty: "入门"
date: 2026-09-29 10:57
updated: 2026-10-04 21:35
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1000
---
[[TOC]]

## 题目描述

给定两个整数，求它们的和。输入为一行两个用空格隔开的整数，输出这两个整数的和。样例：输入 `1 2`，输出 `3`。

## 思路

这是"读入、计算、输出"的最小版本：把一行里的两个整数读进来，直接相加输出即可。题面没给数据范围，用 `ll` 读入可以保证常见的加数范围都不会溢出。

## 参考代码

@include-code(./main.cpp, cpp)

