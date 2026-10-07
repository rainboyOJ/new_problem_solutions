---
oj: "roj"
problem_id: "1147"
title: "最高分数的学生姓名"
description: "顺序扫描每名学生的分数与姓名，维护当前最高分及其姓名，只有严格更高分才替换，输出最后的姓名。"
difficulty: "入门"
date: 2026-09-29 20:49
updated: 2026-10-05 03:27
toc: true
tags: ["入门", "数组", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1147
---

[[TOC]]

## 题目描述

输入学生人数 $N$（$N \le 100$），再输入 $N$ 行，每行是「分数 姓名」：分数为不超过 $100$ 的非负整数，姓名不含空格且长度不超过 $20$。要求输出分数最高者的姓名，数据保证最高分只有一位。样例输入 `5 / 87 lilei / 99 hanmeimei / 97 lily / 96 lucy / 77 jim`，输出 `hanmeimei`。

## 思路

顺序扫描每条记录，维护当前最高分与其姓名，只有分数严格大于当前最高分时才同时更新两者，因此并列时保留先到者，扫描结束后留下的姓名就是答案。分数非负，最高分初值取 $-1$ 即可省掉第一位学生的特判；全程只扫一遍，时间复杂度 $O(N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
