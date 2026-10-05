---
oj: "roj"
problem_id: "1339"
title: "【例3-4】求后序遍历"
description: "先序首字符定根、中序里根的位置同时切分两串，递归按\"左 + 右 + 根\"拼出后序。"
difficulty: "普及-"
date: 2026-09-30 05:05
updated: 2026-10-05 10:39
toc: true
tags: ["二叉树", "递归", "分治", "树的遍历", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1339
---

[[TOC]]

## 题目描述

输入同一棵二叉树的先序和中序遍历串（结点为互不相同的小写字母），输出后序遍历串。输入两行依次为先序、中序；输出一行后序。结点数 ≤ 30。

样例：先序 `abdec`、中序 `dbeac` → 后序 `debca`。

## 思路

先序首字符即根；在中序里找到根的位置 k，则左子树恰有 k 个结点，两串按 k 同步切成左右两部分，回拼顺序为"左 + 右 + 根"。

## 参考代码

@include-code(./main.cpp, cpp)