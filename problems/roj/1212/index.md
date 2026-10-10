---
oj: "roj"
problem_id: "1212"
title: "LETTERS"
description: "从左上角做四连通 DFS，用 26 位掩码记录路径上用掉的字母，新字母才可进入；字母不重复蕴含格子不重复，故一个掩码即可替代格子访问数组。"
difficulty: "普及-"
date: 2026-09-29 23:49
updated: 2026-10-05 05:37
toc: true
tags: ["搜索", "DFS", "位运算", "回溯", "python"]
favorite: false
favorite_reason: ""
categories: ["搜索"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1212
---

[[TOC]]

## 题目描述

给出一个 $R\times S$ 的大写字母矩阵（$1\le R,S\le 20$），起点为左上角，每步可向上下左右四连通移动，但不能移向曾经经过的字母（同一字母整条路径只能用一次），求最多能经过几个字母。输入第一行 $R,S$，随后 $R$ 行每行 $S$ 个大写字母；输出这个最大个数。样例输入 `3 6 / HFDFFB / AJHGDH / DGAGEH`，输出 `6`。

## 思路

从左上角做四连通 DFS，用 26 位掩码记录路径上已用掉的字母，目标格字母不在掩码中才可进入。字母不重复蕴含格子不重复，所以一个掩码即可替代访问数组；字母只有 26 种，搜索深度不超过 26，沿途刷新最大值即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
