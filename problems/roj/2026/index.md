---
oj: "roj"
problem_id: "2026"
title: "usaco-2.2.1 序言页码"
description: "每个十进制数位的罗马写法唯一固定（含 IV、IX、XC 等减法组合），按千/百/十/个位四张表逐页拼接 1..N 的罗马表示并累计 7 个字符出现次数。"
difficulty: "入门"
date: 2026-10-01 03:32
updated: 2026-10-06 09:46
toc: true
tags: ["入门", "模拟", "查表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2026
---

[[TOC]]

## 题目描述

给定整数 $N$（$1 \leqslant N < 3500$）。把 $1,2,\dots,N$ 每个页码写成标准罗马数字，统计 `I V X L C D M` 各字符出现总次数，按该顺序每行输出 `字符 次数`，未出现的字符不输出。样例：输入 `5`，输出 `I 7` 与 `V 2`。

## 思路

标准罗马数字每个十进制数位的写法唯一且固定，减法组合只出现在 4 与 9 两列。用千、百、十、个位四张 0..9 片段表把每页逐位拼成罗马数字并累加字符计数，最后按序输出非零项。

## 参考代码

@include-code(./main.cpp, cpp)
