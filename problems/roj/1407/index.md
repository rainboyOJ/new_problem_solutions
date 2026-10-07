---
oj: "roj"
problem_id: "1407"
title: "笨小猴"
description: "统计单词中每个字母出现次数，判断出现最多次数与最少次数之差是否为质数。"
difficulty: "入门"
date: 2026-09-30 09:00
updated: 2026-10-05 23:10
toc: true
tags:
  - 质数判定
  - 字符串统计
favorite: false
favorite_reason: ""
categories:
  - 数学
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1407
---

[[TOC]]

## 题目描述

单词中只含小写字母、长度小于 100。设 $maxn$ 为出现次数最多字母的出现次数，$minn$ 为出现次数最少字母的出现次数（只统计出现过的字母）。若 $maxn - minn$ 是质数，输出两行：`Lucky Word` 和该差值；否则输出 `No Answer` 和 `0`。如输入 `error` 输出 `Lucky Word`、`2`；输入 `olympic` 输出 `No Answer`、`0`。

## 思路

计数数组统计 26 个字母出现次数，只在出现过的字母上取 maxn 和 minn。差值 $d$ 试除判质数，$d < 2$（如 0 或 1）直接判非质数。

## 参考代码

@include-code(./main.cpp, cpp)
