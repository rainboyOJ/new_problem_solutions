---
oj: "roj"
problem_id: "1179"
title: "奖学金"
description: "把「总分降序、语文降序、学号升序」三段规则合成一个排序键 (-总分, -语文, 学号)，一次排序取前 5 名。"
difficulty: "入门"
date: 2026-09-29 22:29
updated: 2026-10-05 04:26
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1179
---

[[TOC]]

## 题目描述

$n$ 名学生（$n<300$）按「总分降序，总分相同语文降序，再相同学号升序」排名，输出前 $5$ 名的学号和总分。学号即输入行号（从 $1$ 开始），每科成绩 $0\sim100$；输入第一行 $n$，之后 $n$ 行每行三个整数。样例输入 `6` ＋ `90 67 80` / `87 66 91` / `78 89 91` / `88 99 77` / `67 89 64` / `78 89 98`，输出 `6 265` / `4 264` / `3 258` / `2 244` / `1 237`。

## 思路

先算出每人总分 $t=c+m+e$，再依次比总分、语文、学号三项排序，取前 $5$ 名输出。学号只是输入行号，不能拿输入顺序当名次。

## 参考代码

@include-code(./main.cpp, cpp)
