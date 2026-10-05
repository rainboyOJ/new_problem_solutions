---
oj: "roj"
problem_id: "1412"
title: "二进制分类"
description: "通过二进制位统计枚举 1~1000 内数字并分类为 A 类数与 B 类数。"
difficulty: "入门"
date: 2026-09-30 09:12
updated: 2026-10-05 23:15
toc: true
tags:
  - "进制转换"
  - "位运算"
  - "模拟"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1412
---

[[TOC]]

## 题目描述

给定正整数范围 $1\sim 1000$。将每个数写成无前导零的二进制，若 $1$ 的个数多于 $0$ 的个数则为 A 类数，否则为 B 类数。无输入，输出两个整数：A 类数个数、B 类数个数。

## 思路

枚举 $x\in[1,1000]$，分别统计其二进制总位数 $L$ 与 $1$ 的个数 $c_1$，则 $0$ 的个数为 $L-c_1$。按 $c_1>L-c_1$ 分类计数即可。

## 参考代码

@include-code(./main.cpp, cpp)
