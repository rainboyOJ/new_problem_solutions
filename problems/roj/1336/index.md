---
oj: "roj"
problem_id: "1336"
title: "【例3-1】找树根和孩子"
description: "每条边只解析一次：parent[y]=x 定根，children[x] 记孩子；编号递增扫描 + 严格大于实现并列取小编号，O(n+m)。"
difficulty: "入门"
date: 2026-09-30 05:56
updated: 2026-10-05 10:12
toc: true
tags: ["入门", "树", "图论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1336
---

[[TOC]]

## 题目描述

$n$ 个编号 $1\sim n$ 的结点和 $m$ 条有向边，每行 `x y` 表示 $y$ 是 $x$ 的孩子，保证构成一棵树（$n\le 100$，$m\le 200$，$x,y\le 1000$）。求树根 `root`、孩子最多的结点 `max`（若并列取编号最小者），以及 `max` 的全部孩子（按编号升序输出）。样例：输入第一行 `8 7`，随后七行 `4 1`、`4 2`、`1 3`、`1 5`、`2 6`、`2 7`、`2 8`；输出三行为 `4`、`2`、`6 7 8`。

## 思路

每条边只解析一次：`parent[y]=x` 记下 $y$ 的父亲，`children[x]` 记下 $x$ 的孩子。树中只有根没有父亲，所以从 $1$ 到 $n$ 递增扫描，第一个不在父亲表里的编号就是根；孩子表最长的结点就是 `max`（编号递增扫描配合严格大于比较，天然实现并列取小编号），它的孩子必须显式排序后再输出，因为输入不保证有序。

## 参考代码

@include-code(./main.cpp, cpp)
