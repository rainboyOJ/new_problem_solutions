---
oj: "roj"
problem_id: "1618"
title: "「一本通 6.1 练习 3」越狱"
description: "正难则反：答案 = m^n − m(m−1)^(n−1)，补集逐位独立相乘，两次模快速幂 O(log n) 出解。"
difficulty: "普及"
date: 2026-09-30 22:18
updated: 2026-10-06 01:18
toc: true
tags: ["数学", "计数", "组合计数", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1618
---

[[TOC]]

## 题目描述

监狱有连续编号为 $1$ 到 $n$ 的 $n$ 个房间，每间关押一名犯人，共有 $m$ 种宗教。若存在相邻两间房间的犯人信仰同一宗教，就可能发生越狱。求可能发生越狱的状态数对 $100003$ 取余的结果。

输入一行两个整数 $m$ 和 $n$（$1 \le m \le 10^8$，$1 \le n \le 10^{12}$），输出可能越狱的状态数 mod $100003$。样例输入 `2 3`，样例输出 `6`。

## 思路

正难则反：全部状态数为 $m^n$；「不越狱」要求所有相邻房间信仰都不同，第 $1$ 间有 $m$ 种选法，之后每间避开左邻恒有 $m-1$ 种，共 $m(m-1)^{n-1}$ 个。答案 $= m^n - m(m-1)^{n-1} \bmod 100003$，$n$ 高达 $10^{12}$，两个幂用快速幂求，减法为负时补回模数。

## 参考代码

@include-code(./main.cpp, cpp)
