---
oj: "roj"
problem_id: "1367"
title: "查找二叉树(tree_a)"
description: "孩子链表读入建树，没当过儿子的编号即根；中序递归遍历用计数器数访问名次，值等于 x 时输出并停止，O(n) 完成。"
difficulty: "入门"
date: 2026-09-30 07:15
updated: 2026-10-12 14:40
toc: true
tags: ["入门", "树形结构", "递归", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1367
---

[[TOC]]

## 题目描述

一棵 $n$（$n \leqslant 100$）个结点的二叉树用孩子链表存储：第一行是结点个数 $n$，第二行是要查找的值 $x$，接下来 $n$ 行每行三个数，依次是结点的值、左儿子编号、右儿子编号（$0$ 表示空，根没有直接给出）。按中序顺序（左子树 $\to$ 根 $\to$ 右子树）访问这棵树，输出值为 $x$ 的结点是第几个被访问的结点（从 $1$ 数起）。样例中树的中序序列为 $29, 12, 8, 15, 23, 5, 10$，值 $15$ 排第 $4$，故输入 $7$、$15$ 和 $7$ 行结点表时输出 $4$。

## 思路

按父亲孩子表示法的二叉树特化建表：一个结点的值、左儿子、右儿子、父亲收进同一个 `node[u]`（C++ 是 `struct Node`，Python 是 `Node` 对象）。读入第 $i$ 行时写入 `node[i]` 的值和左右孩子，顺手写 `node[儿子].fa = i`，于是除根外每个结点的 `fa` 都不为 0，**`fa == 0` 的那个点就是根**，不必另开数组去判"谁没当过儿子"。再按"左 $\to$ 根 $\to$ 右"递归中序遍历，用计数器数访问名次，值等于 $x$ 时输出并停止。注意树不一定满足二叉排序树性质，不能按值二分，只能老实遍历，$O(n)$ 即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
