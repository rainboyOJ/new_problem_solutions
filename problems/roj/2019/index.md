---
oj: "roj"
problem_id: "2019"
title: "usaco-1.5.3 特殊的质数肋骨"
description: "由 {2,3,5,7} 逐位接 {1,3,7,9} 生长，每次试除判素，保留仍是质数的前缀。"
difficulty: "普及-"
date: 2026-10-01 03:18
updated: 2026-10-06 09:41
toc: true
tags:
  - 数论
  - 素数
  - 搜索
  - usaco
  - python
favorite: false
favorite_reason: ""
categories:
  - USACO
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2019
---

[[TOC]]

## 题目描述

给定 N（1 ≤ N ≤ 8），求所有长度为 N 的“特殊质数”：从最高位开始切下任意前缀（含完整数本身）都必须是质数。按升序每行输出一个。

## 思路

一位数特殊质数只有 {2,3,5,7}。长度大于 1 时，末位只能是 {1,3,7,9}，否则会被 2 或 5 整除。逐位生长：对当前每个合法前缀，尝试接一位并试除判素，保留仍是质数的候选。由于按前缀升序、末位升序扩展，输出天然有序。

## 参考代码

@include-code(./main.cpp, cpp)
