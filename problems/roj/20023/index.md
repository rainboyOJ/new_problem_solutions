---
oj: "roj"
problem_id: "20023"
title: "琴"
description: "值域只有 1~50，排序后相邻差 ≤1 等价于难度值连续不断档，答案是从区间最小难度到第一个空档的出现次数之和。"
difficulty: "普及-"
date: 2026-08-29 00:08
updated: 2026-10-07 10:45
toc: true
tags: ["前缀和", "桶", "区间"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20023
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的序列 $a_i$（$1\le a_i\le 50$）。$m$ 次询问，每次给出区间 $[l,r]$：把区间内的数从小到大排序，从第一个数开始向后走，要求相邻两数差为 $0$ 或 $1$，否则停止。输出每天实际练习的曲目数。

输入：$n$、序列、$m$，以及 $m$ 组 $l_i,r_i$。输出：$m$ 行答案。数据范围 $n,m\le 10^5$。

## 思路

排序后相邻差 $\le 1$ 等价于从区间最小难度起连续不断档。对每个难度值 $1\sim50$ 建前缀和，每次询问先找最小出现难度，再累加直到第一个出现次数为 $0$ 的难度。复杂度 $O((n+m)\cdot 50)$。

## 参考代码

@include-code(./main.cpp, cpp)
