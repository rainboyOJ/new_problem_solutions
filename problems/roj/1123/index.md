---
oj: "roj"
problem_id: "1123"
title: "图像相似度"
description: "把两幅 01 图像展开成一维序列，线性统计对应位置像素相等的个数，再按百分比输出。"
difficulty: "入门"
date: 2026-09-29 19:49
updated: 2026-10-05 02:45
toc: true
tags: [python, 模拟, 输入输出, 数组]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1123
---

[[TOC]]

## 题目描述

给出两幅大小相同的黑白图像，每幅是一个 $m \times n$ 的 0-1 矩阵。若两幅图像在同一位置的像素颜色相同，则称该位置为相同像素点，两幅图像的相似度定义为相同像素点数占总像素点数的百分比。
输入格式：第一行是 $m$、$n$（$1 \le m, n \le 100$）；之后 $m$ 行每行 $n$ 个 0 或 1 表示第一幅图像，再 $m$ 行每行 $n$ 个 0 或 1 表示第二幅图像。输出格式：相似度百分比，精确到小数点后两位。
输入样例：`3 3`，第一幅为 `1 0 1` / `0 0 1` / `1 1 0`，第二幅为 `1 1 0` / `0 0 1` / `0 0 1`；输出样例：`44.44`。
## 思路

直接把两幅图像逐位置比较：读入两个矩阵后双重循环统计 $A_{i,j} = B_{i,j}$ 的个数 `same`，相似度就是 `same / (m*n) * 100`，用浮点输出并保留两位小数即可。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
