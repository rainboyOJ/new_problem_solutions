---
oj: "roj"
problem_id: "1365"
title: "FBI树"
description: "递归分治：按子串区间直接构造 FBI 树并后序输出，根类型由子串含 0/1 情况决定。"
difficulty: "入门"
date: 2026-09-30 07:15
updated: 2026-09-30 07:17
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

## 形式化题目

给定长度为 $2^N$ 的 01 串 $S$（$0\leqslant N\leqslant 10$）。

定义函数 $f(l,r)$ 表示子串 $S[l\dots r-1]$ 所对应子树的后序遍历序列：

$$
f(l,r)=\begin{cases}
\text{kind}(S[l]) & r-l=1 \\
f(l,mid)+f(mid,r)+\text{kind}(S[l\dots r-1]) & \text{否则}
\end{cases}
$$

其中 $mid=(l+r)/2$，$\text{kind}(T)$ 为 B/I/F 判断：全 0 为 B，全 1 为 I，否则为 F。

求 $f(0,2^N)$。

## 正解

### 思路

FBI 树的构造规则和后序遍历顺序天然适合递归：

1. 根结点类型由当前子串整体决定。
2. 子串长度大于 1 时，从中间分成左右两段，分别递归构造左右子树。
3. 输出顺序是“左子树 → 右子树 → 根”。

因此不需要显式建树，直接用递归函数返回每个子串对应子树的后序序列即可。

类型判断可以通过成员检查完成：子串中不含 `'1'` 为 B，不含 `'0'` 为 I，否则为 F。

### 代码

@include-code(./main.py, python)

### 复杂度

设 $L=2^N$，递归树共有 $2L-1$ 个结点，每层类型判断的总代价为 $O(L)$，总时间复杂度 $O(L\log L)$。递归栈深度 $O(\log L)$，输出长度 $2L-1$，空间复杂度 $O(L\log L)$（含缓存）。对于 $N\leqslant 10$ 完全足够。

## 总结

本题是“递归 + 分治 + 后序遍历”的直接应用。关键在于把“子串区间”和“子树”一一对应，后序序列在递归返回时自然拼接出来。
