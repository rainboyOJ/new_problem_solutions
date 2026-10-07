---
oj: "roj"
problem_id: "3008"
title: "递归实现排列型枚举"
description: "通过按位决策的回溯搜索树，依次枚举未使用的数字生成字典序排列。"
difficulty: "入门"
date: 2026-10-01 09:32
updated: 2026-10-06 11:13
toc: true
tags:
  - "递归"
  - "搜索"
  - "回溯"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3008
---

[[TOC]]

## 题目描述

把 $1 \sim n$ 这 $n$ 个整数排成一行，输出所有可能的次序（$1 \le n \le 9$）。**输入**：一个整数 $n$。**输出**：按字典序从小到大输出所有方案，每行一个，同行相邻两数用空格隔开。例如 $n=3$ 时输出：

```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

## 思路

把排列看成从左到右逐个位置填数字：`dfs(pos)` 从 1 到 n 依次尝试每个未使用的数字填进第 pos 个位置，标记后递归、返回后取消标记（回溯），pos 到达 n 时输出当前排列。由于每层从小到大枚举，输出天然满足字典序。

## 参考代码

@include-code(./main.cpp, cpp)
