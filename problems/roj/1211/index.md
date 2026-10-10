---
oj: "roj"
problem_id: "1211"
title: "判断元素是否存在"
description: "把生成规则 y→2y+1、y→3y+1 反过来用：x 的父亲只能是 (x-1)/2 或 (x-1)/3，反向递归收缩并记忆化，判断 x 能否缩回种子 k。"
difficulty: "普及-"
date: 2026-09-29 23:43
updated: 2026-10-05 05:37
toc: true
tags: ["搜索", "递归", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: ["搜索"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1211
---

[[TOC]]

## 题目描述

集合 $M$ 由种子 $k$ 与规则 $y \mapsto 2y+1$、$y \mapsto 3y+1$ 生成，除此外无其他元素。给定无符号整数 $k$ 和 $x$（$x \leqslant 100000$），判断 $x$ 是否属于 $M$，是则输出 `YES`，否则输出 `NO`。输入一行，逗号（也可能是空格）分隔两个整数 $k,\ x$。

样例输入 `0,22` → 输出 `YES`（路径 $0 \to 1 \to 3 \to 7 \to 22$）。

## 思路

生成规则都严格递增，反过来 $x$ 的父亲只可能是 $(x-1)/2$ 或 $(x-1)/3$（要求整除）。从 $x$ 反向递归收缩，配 `memo` 记忆化：若 $x<k$ 不可达，$x=k$ 命中可达，否则任一父亲递归可达即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)