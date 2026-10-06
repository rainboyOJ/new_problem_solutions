---
oj: "roj"
problem_id: "3506"
title: "求先序遍历"
description: "后序末位定根、中序按下标切成左右子树，在两串切片上递归拼出根+左+右即得先序，无需显式建树。"
difficulty: "普及-"
date: 2026-10-02 04:16
updated: 2026-10-06 12:15
toc: true
tags: ["二叉树", "递归", "遍历", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3506
---

[[TOC]]

## 题目描述

给定一棵二叉树的中序遍历与后序遍历（结点为互不相同的大写字母，长度 $\le 8$），求先序遍历。

输入共两行，第一行为中序遍历，第二行为后序遍历。输出一行先序遍历。

样例：中序 `BADC`、后序 `BDCA`，输出 `ABCD`。

## 思路

后序最后一个字符是当前子树的根；在中序中找到该根，左边即左子树、右边即右子树。递归输出根、左子树、右子树即得先序。空子树直接返回。

## 参考代码

@include-code(./main.cpp, cpp)
