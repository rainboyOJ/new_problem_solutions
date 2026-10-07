---
oj: "roj"
problem_id: "1338"
title: "【例3-3】医院设置"
description: "把父子链接当作无向边，Floyd 求全源最短路，再枚举医院位置取人口加权距离和的最小值。"
difficulty: "入门"
date: 2026-09-30 05:57
updated: 2026-10-05 10:38
toc: true
tags:
  - 图论
  - 最短路
  - Floyd
  - 二叉树
  - Python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1338
---
[[TOC]]
## 题目描述
给定 n 个结点的二叉树，结点 i 住 p_i 人，左、右孩子为 l_i、r_i（0 表示无孩子）。相邻结点距离为 1，要在某一结点建医院，使所有居民到医院的距离之和最小。输入：第一行 n；接下来 n 行每行 p_i、l_i、r_i。输出：最小距离和。n ≤ 100。
样例输入：`5 / 13 2 3 / 4 0 0 / 12 4 5 / 20 0 0 / 40 0 0`，样例输出：`81`
## 思路
把父子链接当作无向边，Floyd 求全源最短路；枚举医院位置，按人口加权求距离和，取最小值。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
