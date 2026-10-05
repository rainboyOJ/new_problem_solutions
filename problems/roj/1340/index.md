---
oj: "roj"
problem_id: "1340"
title: "【例3-5】扩展二叉树"
description: "顺序消费扩展先序序列递归还原二叉树，再做一次中序、一次后序遍历输出。"
difficulty: "入门"
date: 2026-09-30 05:57
updated: 2026-10-05 10:38
toc: true
tags: ["二叉树", "递归", "遍历"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1340
---

[[TOC]]

## 题目描述

把二叉树中所有空结点用 `.` 补齐，得到的扩展二叉树先序序列能唯一确定这棵二叉树。给定一行扩展先序序列（大写字母是结点，`.` 是空结点），输出原二叉树的中序序列和后序序列，各占一行；样例输入 `ABD..EF..G..C..`，输出第一行 `DBFEGAC`、第二行 `DFGEBCA`。

## 思路

扩展先序序列的结构天然是递归的：`树 = 根字符 + 左子树 + 右子树`，`.` 表示空树。从左到右顺序读字符，遇字母就建根结点并递归构造左右子树，遇 `.` 就返回空，即可还原整棵树；再分别做一次中序（左—根—右）与后序（左—右—根）遍历输出。总复杂度 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
