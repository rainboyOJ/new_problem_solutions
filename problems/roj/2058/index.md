---
oj: "roj"
problem_id: "2058"
title: "usaco-3.4.2 美国血统"
description: "利用前序首字符确定二叉树根节点并在中序遍历中划分左右子树，分治递归生成后序遍历。"
difficulty: "入门"
date: 2026-10-01 05:31
updated: 2026-10-06 10:36
toc: true
tags:
  - 二叉树
  - 递归
  - 分治
favorite: false
favorite_reason: ""
categories:
  - 树结构
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2058
---

[[TOC]]

## 题目描述

给定一棵二叉树的中序遍历序列与前序遍历序列，节点用唯一的大写字母表示（$n \le 26$），求其后序遍历序列。输入第一行为中序遍历，第二行为同一棵树的前序遍历；输出单独一行后序遍历，如输入 `ABEDFCHG` 与 `CBADEFGH` 时输出 `AEFDBHGC`。

## 思路

前序序列的第一个字符就是根节点；由于节点字母唯一，在中序序列中找到根的位置，左边是左子树、右边是右子树，且左子树长度已知，可在前序中同样切分出左右子树的前序序列。按「递归左子树、递归右子树、输出根」的顺序分治即可直接打印后序遍历，无需显式建树。

## 参考代码

@include-code(./main.cpp, cpp)
