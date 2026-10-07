---
oj: "roj"
problem_id: "1463"
title: "「一本通 2.1 练习 7」门票"
description: "把递推数列看成函数迭代，逐项模拟并用哈希集合记住出现过的值，首次撞上旧值的下标即答案，超过 2×10^6 步输出 -1。"
difficulty: "普及-"
date: 2026-09-30 12:24
updated: 2026-10-06 00:14
toc: true
tags: ["模拟", "哈希表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1463
---

[[TOC]]

## 题目描述

给定数列 ${a_n}$：$a_0=1$，$a_{i+1}=(A\times a_i + a_i\bmod B)\bmod C$，其中 $0\le A,B,C\le 10^9$。输入一行三个整数 $A,B,C$，输出该数列第一次出现重复项的标号，若该标号超过 $2\times10^6$ 则输出 $-1$。样例输入 `2 2 9`，样例输出 `4`。

## 思路

递推式是一个函数迭代，每项只由前一项决定，所以重复必然出现。从 $a_0=1$ 起逐项模拟，用哈希集合记录已经出现过的值，第一次撞上旧值的下标就是答案。值域 $C$ 可达 $10^9$ 开不下标记数组，但模拟步数不超过 $2\times10^6$，集合大小只与出现过的项数有关；注意 $a_0=1$ 也要先放进集合，且“超过 $2\times10^6$”不含恰好等于。

## 参考代码

@include-code(./main.cpp, cpp)
