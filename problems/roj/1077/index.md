---
oj: "roj"
problem_id: "1077"
title: "统计满足条件的4位数"
description: "把每个四位数的个位与其余三位数字之和比较，统计大于零的个数。"
difficulty: "入门"
date: 2026-09-29 17:42
updated: 2026-10-05 00:21
toc: true
tags: ["入门", "模拟", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1077
---

[[TOC]]

## 题目描述

给定 $n$（$n\le 100$）个四位数，统计满足「个位数字减去千位、百位、十位上的数字的结果大于零」的数的个数。

输入两行，第一行为 $n$，第二行为 $n$ 个四位数；输出一行一个整数表示答案。样例输入：`5` 加 `1234 1349 6119 2123 5017`，样例输出：`3`。

## 思路

对每个四位数拆出千位、百位、十位、个位，判定 `d - a - b - c > 0`，满足则计数加一，遍历一遍即可。

## 参考代码

@include-code(./main.cpp, cpp)