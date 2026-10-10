---
oj: "roj"
problem_id: "1575"
title: "「一本通 5.2 例 1」二叉苹果树"
description: "二叉树树形背包：枚举左右子树各保留多少条边完成状态转移。"
difficulty: "普及"
date: 2026-09-30 19:26
updated: 2026-10-06 00:48
toc: true
tags:
  - "动态规划"
  - "树形 DP"
  - "背包 DP"
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1575
---

[[TOC]]

## 题目描述

有一棵 $N$ 个节点的二叉苹果树，树根为 $1$，非叶节点恰有两个子节点。每条树枝上有一个非负整数苹果数。给定要保留的树枝数 $Q$，求能保留的最多苹果数。

输入第一行是 $N,Q$，接下来 $N-1$ 行每行给出一条树枝两端的节点编号和苹果数。输出一行，表示最多能留住的苹果数。

数据范围：$1 \le Q \le N \le 100$，每根树枝苹果数不超过 $30000$。

## 思路

设 $f(u,k)$ 表示以 $u$ 为根的子树保留 $k$ 条边的最大苹果数。保留 $k$ 条边时要么只走左（消耗 1 条边），要么只走右（消耗 1 条边），要么两边都走并枚举左右子树分别分配 $i$ 和 $k-2-i$ 条边。从根节点记忆化搜索得 $f(1,Q)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
