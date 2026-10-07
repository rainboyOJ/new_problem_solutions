---
oj: "roj"
problem_id: "1362"
title: "家庭问题"
description: "把每个关系看作无向边，用并查集合并家庭成员，最后按代表元统计家庭数与最大家庭规模。"
difficulty: "入门"
date: 2026-09-30 07:02
updated: 2026-10-05 12:00
toc: true
tags:
  - 并查集
  - 连通分量
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1362
---

[[TOC]]

## 题目描述

有 $n$ 个人（编号 $1 \sim n$）和 $k$ 个关系 $(a,b)$，表示 $a$ 与 $b$ 是同一家庭的成员，关系可传递。输入第一行 $n,k$（$1 \le n \le 100$），后接 $k$ 行每行两个整数；输出两个整数，即家庭个数与最大家庭人数。

样例输入

```text
6 3
1 2
1 3
4 5
```

样例输出：`3 3`。

## 思路

把每个人看作点、每个关系看作无向边，同一连通块的人就是一家人，问题即求连通块个数与最大连通块大小。用并查集依次合并每个关系中的两人，再对每个人查代表元统计各家庭人数，人数非零的家庭数就是答案第一部分，其中的最大值是第二部分。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
