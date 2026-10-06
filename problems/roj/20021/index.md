---
oj: "roj"
problem_id: "20021"
title: "画"
description: "3×3 小矩阵只有 3^9 种形态，把每块压缩成三进制整数用 bool 数组标记，O(1) 去重计数。"
difficulty: "入门"
date: 2026-08-29 00:09
updated: 2026-10-06 09:04
toc: true
tags: ["哈希", "枚举"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20021
---

[[TOC]]

## 题目描述

给定 $n\times m$ 的像素矩阵，$n,m$ 均为 $3$ 的倍数，每格为 R/G/B 之一。把矩阵按行列各均分成 $3\times 3$ 的小矩阵，去重后求不同小矩阵的数量。

输入第一行 $n,m$，接下来 $n$ 行每行一个长度 $m$ 的 RGB 字符串；输出一个整数表示重复度。样例：`3 3` 的三行 `RGB` 输出 `1`；`6 6` 的四色块样例输出 `3`。$100\%$ 数据 $n,m\le 3000$。

## 思路

3x3 小矩阵只有 $3^9=19683$ 种形态，按行优先把每块压成三进制整数（R=0、G=1、B=2），用 `bool seen[19683]` 标记，首次出现就计入答案。

## 参考代码

@include-code(./main.cpp, cpp)
