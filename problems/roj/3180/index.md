---
oj: "roj"
problem_id: "3180"
title: "「The Counting Problem」 计数问题"
description: "数位统计前缀差：cnt(n,d) 逐位拆 high/cur/low 计算每位贡献，0 需扣掉前导零情形，答案作 cnt(b)-cnt(a-1)。"
difficulty: "普及"
date: 2026-10-01 23:31
updated: 2026-10-06 11:58
toc: true
tags:
  - 数位DP
  - 递推
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3180
---

[[TOC]]

## 题目描述

给定整数 $a,b$，统计 $[\min(a,b),\max(a,b)]$ 内所有整数的十进制写法中数字 $0\sim 9$ 各出现多少次。多组数据，每行两个整数，读入 `0 0` 结束（该行不处理），每组输出十个空格隔开的整数，依次为 $0,1,\dots,9$ 的出现次数。$0<a,b<10^8$。

样例输入：`1 10`、`0 0`；样例输出：`1 2 1 1 1 1 1 1 1 1`。

## 思路

答案作前缀差 $\mathrm{cnt}(b,d)-\mathrm{cnt}(a-1,d)$，其中 $\mathrm{cnt}(n,d)$ 统计 $1\sim n$ 中 $d$ 的出现次数；逐位（个位、十位、……）把 $n$ 拆成 high/cur/low，枚举当前位等于 $d$ 的数累加，$d=0$ 时去掉前导零（要求高位不全为 0）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
