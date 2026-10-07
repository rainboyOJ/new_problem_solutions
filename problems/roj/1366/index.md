---
oj: "roj"
problem_id: "1366"
title: "二叉树输出(btout)"
description: "先序首字符定根、中序中根的位置切分左右子树，递归求出每棵子树的叶子数即结点长度，再按先序输出「字符 × 长度」。"
difficulty: "普及-"
date: 2026-09-30 07:15
updated: "2026-10-05 12:08"
toc: true
tags: ["二叉树", "树的遍历", "递归", "记忆化", "哈希表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1366
---

[[TOC]]

## 题目描述

输入两行字符串，分别是一棵二叉树（字符互不重复）的先序和中序序列。按凹入表示法输出这棵树：按先序，每个结点占一行，该行由它的字符重复「结点长度」次，行数等于结点数；叶结点长度为 $1$，非叶结点长度等于左右子树长度之和，即长度等于子树中的叶子数。样例输入 `ABCDEFG` 与 `CBDAFEG`，样例输出依次为 `AAAA`、`BB`、`C`、`D`、`EE`、`F`、`G`。

## 思路

先序首字符是根，它在中序序列中的位置把左右子树切开，递归下去就能还原整棵树；空子树叶子数记 $0$，于是 $n \le 1$ 时长度就是 $0/1$，只有一个孩子的结点无需分情况讨论。先求出每个结点的长度（子树叶子数），再按先序输出「字符 × 长度」。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
