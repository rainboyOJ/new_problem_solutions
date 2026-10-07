---
oj: "roj"
problem_id: "3644"
title: "[noip2017-普及] 成绩"
description: "把 20%/30%/50% 权重整体乘 100 化成整数权重 2/3/5，加权和由数据保证被 10 整除，全程整数运算、一次整除即得整数总评，避开浮点精度与 90.0 输出格式问题。"
difficulty: "入门"
date: 2026-10-02 12:32
updated: 2026-10-06 15:50
toc: true
tags: ["入门", "数学", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3644
---

[[TOC]]

## 题目描述

输入三个非负整数 $A,B,C$（作业、小测、期末成绩，满分 $100$，且均为 $10$ 的倍数），按权重 $20\%,30\%,50\%$ 计算总成绩，输出一个整数。

## 思路

把权重整体乘 $100$ 化为整数 $2,3,5$，则 $S=(2A+3B+5C)/10$。数据保证 $A,B,C$ 是 $10$ 的倍数，分子必被 $10$ 整除，一次整数整除即得答案。

## 参考代码

@include-code(./main.cpp, cpp)
