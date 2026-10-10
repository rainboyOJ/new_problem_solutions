---
oj: "roj"
problem_id: "1127"
title: "图像旋转"
description: "顺时针旋转矩阵 90°：新矩阵的第 i 行是原矩阵第 i 列从下到上读取。"
difficulty: "入门"
date: 2026-09-29 20:02
updated: 2026-10-05 02:40
toc: true
tags: ["矩阵", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1127
---

[[TOC]]

## 题目描述

输入 $n$ 行 $m$ 列（$1\le n,m\le 100$，像素为 $0\sim 255$ 的整数）的图像，将它顺时针旋转 $90^\circ$ 后输出 $m$ 行、每行 $n$ 个整数。样例：输入 `3 3 / 1 2 3 / 4 5 6 / 7 8 9`，输出 `7 4 1 / 8 5 2 / 9 6 3`。

## 思路

顺时针旋转 $90^\circ$ 后，新矩阵第 $i$ 行对应原矩阵第 $i$ 列，且读取方向由从上往下变为从下往上，即 $b_{i,j}=a_{n-1-j,\,i}$。按此映射双重循环输出即可，时间与空间复杂度均为 $O(n\cdot m)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
