---
oj: "roj"
problem_id: "3006"
title: "递归实现指数型枚举"
description: "每个整数「选 / 不选」构成一棵深度 n 的满二叉决策树，递归遍历即得全部 2^n 个子集；升序天然成立。"
difficulty: "入门"
date: 2026-10-01 09:37
updated: 2026-10-06 10:57
toc: true
tags: ["递归", "搜索", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3006
---

[[TOC]]

## 题目描述

给定 $n$（$1 \le n \le 15$），从 $1 \sim n$ 任选若干个数，每行输出一种方案（升序、单空格分隔，不选则空行），行序任意。

## 思路

把每个数看成选/不选决策，$n$ 个数构成满二叉决策树，$2^n$ 个叶子即全部子集；先递归不选再递归选，路径下标天然升序。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
