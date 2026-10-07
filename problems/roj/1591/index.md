---
oj: "roj"
problem_id: "1591"
title: "「一本通 5.3 练习 4」数字计数"
description: "按位差分统计区间数码个数。"
difficulty: "普及-"
date: 2026-09-30 20:38
updated: 2026-10-07 13:50
toc: true
tags: ["数位", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "3576"
    reason: "B 直接沿用 A 教的按位三段闭式计数（同一 higher/cur/lower 分解与到顶组补量），只把统计目标从数码 2 推广到 0~9 并加 0 的前导零修正，A 因此是 B 的前置台阶。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1591
---

[[TOC]]

## 题目描述

给定正整数 $a,b$（$1 \le a \le b \le 10^{12}$），统计区间 $[a,b]$ 中每个整数十进制表示里数码 $0\sim9$ 各出现多少次，顺序输出。
输入一行两个整数 $a,b$；输出一行 $10$ 个整数。样例：输入 `1 99`，输出 `9 20 20 20 20 20 20 20 20 20`。

## 思路

用 $F(n)$ 表示 $1\sim n$ 中各数码出现次数，答案为 $F(b)-F(a-1)$；对每位按 $high,cur,low$ 三段直接计算闭式贡献，统计 $0$ 时跳过前导零。

## 参考代码

@include-code(./main.cpp, cpp)
