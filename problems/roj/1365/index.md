---
oj: "roj"
problem_id: "1365"
title: "FBI树"
description: "递归分治：按子串区间直接构造 FBI 树并后序输出，根类型由子串含 0/1 情况决定。"
difficulty: "入门"
date: 2026-09-30 07:15
updated: 2026-10-05 12:07
toc: true
tags: ["递归", "分治", "二叉树", "后序遍历"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1365
---

[[TOC]]

## 题目描述

给定长度为 $2^N$ 的 01 串（$0\leqslant N\leqslant 10$）。按规则构造 FBI 树：根结点类型由整串决定（全 0 为 B，全 1 为 I，否则为 F）；长度大于 1 时从中间分成左右等长子串，分别递归构造左右子树。输出该树的后序遍历序列。

**输入**：第一行整数 $N$，第二行 01 串。  
**输出**：一行字符串，即后序遍历序列。

样例输入：`3` / `10001011`，样例输出：`IBFBBBFIBFIIIFF`。

## 思路

子串区间与 FBI 子树一一对应。递归处理左右两半，返回后序序列，再拼接根结点类型即可。长度 1 时直接返回该字符对应的 B/I。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
