---
oj: "roj"
problem_id: "1171"
title: "大整数的因子"
description: "把 30 位大整数按字符串读入，逐位递推余数 r = (r*10+d) % k，判断 2~9 中哪些数能整除它。"
difficulty: "入门"
date: 2026-09-29 21:51
updated: 2026-10-05 04:10
toc: true
tags:
  - "大整数"
  - "同余"
  - "模拟"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1171
---

[[TOC]]

## 题目描述

给出一个位数不超过 30 的十进制非负整数 $c$，求所有满足 $2 \le k \le 9$ 且 $c \bmod k = 0$ 的 $k$。若存在，按从小到大输出，相邻两数用一个空格隔开；若不存在，输出 `none`。样例输入 `30`，输出 `2 3 5 6`。

## 思路

$c$ 有 30 位，普通整数存不下，所以按字符串从高位到低位逐位扫描，对每个 $k$ 维护余数 $r \leftarrow (10r + d) \bmod k$；扫完若 $r=0$ 说明 $c$ 能被 $k$ 整除。$k$ 只有 2 到 9 共 8 个，每个单独扫一遍即可，时间复杂度 $O(8|c|)$。

## 参考代码

@include-code(./main.cpp, cpp)
