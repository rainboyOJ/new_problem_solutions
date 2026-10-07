---
oj: "roj"
problem_id: "3530"
title: "[NOIP2004-普及] FBI 树"
description: "递归处理 01 串：先递归左右两半，返回前把当前子串类型 B/I/F 写入答案，调用顺序即后序遍历。"
difficulty: "普及"
date: 2026-10-02 05:39
updated: 2026-10-06 13:12
toc: true
tags: ["二叉树", "递归", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3530
---

[[TOC]]

## 题目描述

由 `0`/`1` 组成的串分三类：全 `0` 为 B，全 `1` 为 I，两者都有为 F。给定长度 $2^N$ 的 `01` 串，递归构造 FBI 树：根类型等于整串类型；长度大于 1 时从中间对半分为左右子串，分别递归构造左右子树。输出后序遍历序列。

输入：第一行 $N(0\le N\le 10)$，第二行长度为 $2^N$ 的 `01` 串。输出：后序字符串。

样例输入：
```text
3
10001011
```
样例输出：`IBFBBBFIBFIIIFF`。

## 思路

递归处理子串 `[l,r]`：先递归左半 `[l,mid]`，再递归右半 `[mid+1,r]`，返回前把当前子串类型追加进答案。调用顺序即后序遍历，不必显式建树。类型判断只看该子串里是否同时出现 `0` 和 `1`。

## 参考代码

@include-code(./main.cpp, cpp)
