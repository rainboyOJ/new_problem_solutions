---
oj: "roj"
problem_id: "1309"
title: "【例1.6】回文数(Noip1999)"
description: "模拟 N 进制回文数生成：数码数组逐位做 a + reverse(a) 并处理进位，至多 30 步判回文；必须按数码面值直接模拟，不能转整数（数据里有数码 ≥ N 的输入）。"
difficulty: "入门"
date: 2026-09-30 04:18
updated: 2026-10-05 09:01
toc: true
tags: ["入门", "高精度", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1309
---

[[TOC]]

## 题目描述

若一个数（首位不为零）从左向右读与从右向左读都一样，称之为回文数。给定进制 $N$（$2 < N \leqslant 10$ 或 $N = 16$）和一个 $N$ 进制数 $M$（数码用 `0`–`9`、`A`–`F` 表示），定义一步操作为：把 $M$ 与"它的数码反转得到的数"做一次 $N$ 进制加法。求最少几步能得到回文数；若 $30$ 步以内（含 $30$ 步）不能得到，输出 `Impossible`。若 $M$ 本身就是回文数，答案为 $0$。例如 10 进制 $87$：$87+78=165 \to 165+561=726 \to 726+627=1353 \to 1353+3531=4884$，共 $4$ 步。

**输入**：一行，进制 $N$ 和 $N$ 进制数 $M$。**输出**：最少步数，或 `Impossible`。样例：输入 `9 87`，输出 `6`。

## 思路

把 $M$ 按字符面值直接读进低位在前的数码数组（不要转整数：数据里存在数码值 $\geqslant N$ 的输入，如 `2 37`，转整数语义就错了），然后反复做「$a \leftarrow a + \operatorname{reverse}(a)$」的 $N$ 进制加法：逐位求和后从低位到高位每位做一次除 $N$ 取余，最高位进位直接追加。第 $0$ 步先判回文（覆盖初始即回文的情形），之后每做一步判一次，$30$ 步用尽仍未回文就输出 `Impossible`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
