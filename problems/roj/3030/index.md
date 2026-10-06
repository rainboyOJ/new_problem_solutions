---
oj: "roj"
problem_id: "3030"
title: "火车进栈"
description: "DFS 按「先出栈、后进栈」分支天然按字典序枚举出站序列，收满前 20 个立即整树剪枝。"
difficulty: "普及-"
date: 2026-10-01 11:03
updated: 2026-10-06 11:20
toc: true
tags: ["栈", "dfs", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3030
---

[[TOC]]

## 题目描述

$n$ 列火车按 $1\sim n$ 的顺序依次进站，车站是一个栈。每次可以选择让下一列火车进栈，或让栈顶火车出站。按字典序输出前 20 种可能的出站序列，每行一种、无空格。$1\le n\le 20$。

样例输入 `3`，输出 `123`、`132`、`213`、`231`、`321`。

## 思路

每个状态优先尝试「出栈」再「进栈」，DFS 到达叶子的顺序就是出站序列的字典序；收满 20 个后立即剪枝返回。

## 参考代码

@include-code(./main.cpp, cpp)
