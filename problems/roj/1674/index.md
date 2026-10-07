---
oj: "roj"
problem_id: "1674"
title: "选小寿星"
description: "约瑟夫报数变体：女生有 2 次机会，用循环队列带机会计数直接模拟，O(mn) 出解。"
difficulty: "入门"
date: 2026-10-01 01:37
updated: 2026-10-06 01:49
toc: true
tags: ["模拟", "约瑟夫问题", "队列"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1674
---

[[TOC]]

## 题目描述

$m$ 名学生围成一个圈，编号 $1 \sim m$，从 1 号开始沿圈连续报数 $1, 2, 3, \dots$：报到 $n$ 的人出局，他的下一位从 1 重新报数，直到只剩 1 人。特殊规则：女生（标记为 0）有 2 次机会，第 1 次数到 $n$ 不出局，第 2 次才出局；男生数中即出局。

输入第一行为 $m$（$m \leqslant 20$），第二行为 $m$ 个整数（1 表示男生，0 表示女生），第三行为 $n$（$1 \leqslant n \leqslant 9$）；输出最后留下学生的编号。样例：输入 $m=5$，性别 `1 1 0 0 1`，$n=3$，输出 `5`；又如 $m=3$，性别 `1 0 1`，$n=2$，输出 `2`。

## 思路

用循环队列模拟报数：圈内的人按报数顺序入队，队首永远是下一个报数的人，每人的剩余机会 `chances[i]` 为男 1、女 2。每步队首出队报数：没数到 $n$ 就回队尾；数到 $n$ 则报数计数清零并消耗一次机会，还有剩余就回队尾，否则出局不再入队。女生"2 次机会"被完全吸收进 `chances` 初值，总步数 $O(mn)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
