---
oj: "roj"
problem_id: "1116"
title: "最长平台"
description: "扫描数组，维护当前相邻相等连续段长度，取最大值。"
difficulty: "入门"
date: 2026-09-29 19:38
updated: 2026-10-05 02:25
toc: true
tags: ["线性扫描", "迭代器", "Python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1116
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的数组。一个平台指连续且值相同的元素组成的**极大**段，不能向左右延伸。输出最长平台的长度。

## 思路

从左到右扫描，若当前元素与前一个相等则延长当前平台，否则重新开始计数，同时用全局最大值更新答案。

## 参考代码

@include-code(./main.cpp, cpp)
