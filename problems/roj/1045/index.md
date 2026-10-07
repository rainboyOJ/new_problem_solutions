---
oj: "roj"
problem_id: "1045"
title: "收集瓶盖赢大奖"
description: "两条兑换路径满足任意一条即可兑奖：把 10 与 20 命名成阈值常量，一次 or 布尔判定输出 1/0，重点是“或”而非“且”。"
difficulty: "入门"
date: 2026-09-29 15:58
updated: 2026-10-04 22:12
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1045
---

[[TOC]]

## 题目描述

某饮料公司推出“收集瓶盖赢大奖”：拥有 10 个“幸运”瓶盖、或 20 个“鼓励”瓶盖即可兑换大奖。输入一行两个整数（幸运数 a、鼓励数 b），判断能否兑换：能输出 `1`，不能输出 `0`。

输入样例：`11 19` → 输出样例：`1`。

## 思路

两条路径满足任意一条即可，用 `(a >= 10) || (b >= 20)` 判定，再把布尔值翻译成 `1`/`0`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)