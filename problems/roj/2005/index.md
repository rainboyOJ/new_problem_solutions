---
oj: "roj"
problem_id: "2005"
title: "方块转换"
description: "用旋转原语与行反转原语复合出全部 8 种候选图案，按序号从小到大与目标逐表比较，取第一个匹配的序号。"
difficulty: "入门"
date: 2026-10-01 02:26
updated: 2026-10-06 09:21
toc: true
tags: ["模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2005
---

[[TOC]]

## 题目描述

给定两个 $N \times N$（$N \le 10$）黑白方阵 `src` 与 `dst`，判定 `src` 经 #1 旋转 90°、#2 旋转 180°、#3 旋转 270°、#4 水平翻转、#5 翻转后再旋转、#6 不变中哪种变成 `dst`，输出最小序号，无法得到输出 7。

## 思路

旋转 90°（$(r,c)\to(c,N-1-r)$）与水平翻转两个原语复合出全部 8 个候选图案，按序号从小到大比对 `dst`，首个一致的序号即答案，全不匹配输出 7。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
