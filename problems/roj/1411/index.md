---
oj: "roj"
problem_id: "1411"
title: "区间内的真素数"
description: "埃氏筛一次性建出整个值域的素数表，区间内每个数 O(1) 查自身与反序数的素性，逗号拼接输出，无解输出 No。"
difficulty: "入门"
date: 2026-09-30 09:16
updated: 2026-10-05 23:15
toc: true
tags: ["素数", "筛法", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1411
---

[[TOC]]

## 题目描述

如果一个正整数 P 是素数，且它的反序数（十进制数字倒过来组成的正整数，前导 0 自动消失，如 13 的反序数是 31）也是素数，就称 P 为**真素数**。输入两个数 M 和 N（空格间隔，$1 \leqslant M \leqslant N \leqslant 100000$），按从小到大输出 M 和 N 之间（包括端点）的所有真素数，逗号间隔、无空格；若没有真素数则输出 `No`。样例：输入 `10 35`，输出 `11,13,17,31`。

## 思路

反序数可能落在区间之外（如 17 的反序数是 71），所以用埃氏筛把整个值域 $[0, 10^5]$ 一次建成素数表，之后判素都是 $O(1)$ 查表。枚举区间内每个数，查自身与反序数是否都为素数，边枚举边用逗号拼接输出，一个都没找到时输出 `No`。

## 参考代码

@include-code(./main.cpp, cpp)
