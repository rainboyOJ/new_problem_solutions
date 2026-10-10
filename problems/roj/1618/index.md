---
oj: "roj"
problem_id: "1618"
title: "「一本通 6.1 练习 3」越狱"
description: "正难则反：答案 = m^n − m(m−1)^(n−1)，补集逐位独立相乘，两次模快速幂 O(log n) 出解。"
difficulty: "普及"
date: 2026-09-30 22:18
updated: 2026-10-07 13:50
toc: true
tags: ["数学", "计数", "组合计数", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1616"
    reason: "B 在正难则反得到 m^n − m(m−1)^(n−1) 后，直接复用 A 教的三参数 pow 模快速幂算这两个幂，B 的额外台阶是取补集与逐位乘法原理计数。"
  - oj: "roj"
    problem_id: "1326"
    reason: "B 用正难则反得到 m^n−m(m−1)^(n−1) 后，复用 A 教的把指数按二进制拆分求模幂，直接调用 pow 算出两个模幂，只是把 A 的单一幂扩成两个幂；额外台阶是补集计数与乘法原理。"
  - oj: "luogu"
    problem_id: "P1226"
    reason: "B 在得出 m^n − m(m−1)^(n−1) 后，直接照 A 教的 Python 三参数 pow 写 pow(m,n,MOD) 与 pow(m-1,n-1,MOD) 求两个模幂，属模板级复用；B 的额外台阶是正难则反取补集加逐位乘法原理的计数。"
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

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
