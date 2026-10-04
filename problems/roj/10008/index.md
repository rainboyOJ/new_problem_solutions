---
oj: "roj"
problem_id: "10008"
title: "牛半仙的妹子串"
description: "读入时按名字结尾字母分 26 个桶，桶内按（评分降序、同分先读入在前）排好序，询问直接取桶内第 k 个名字。"
difficulty: "普及-"
date: 2026-10-02 17:36
updated: 2026-10-04 21:38
toc: true
tags: ["排序", "分桶", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10008
---

[[TOC]]

## 题目描述

牛半仙有 $n$ 个妹子，每个妹子有一个名字（只含小写字母、长度不超过 50）和一个评分。他要回答 $m$ 个询问 $(x, k)$：名字以字母 $x$ 结尾的妹子中评分第 $k$ 大的妹子的名字，评分相同时先读入的算评分更大；这样的妹子不足 $k$ 个时输出 `Orz YYR tql`。输入第一行 $n, m$，接下来 $n$ 行每行一个名字和评分，接下来 $m$ 行每行一个字母 $x$ 和正整数 $k$。$n, m \leqslant 10^5$，$k \leqslant n$。

样例：输入 `5 2` / `aaa 1` / `aa 2` / `a 3` / `ab 3` / `bb 4` / `b 2` / `a 4`，输出 `ab` / `Orz YYR tql`。

## 思路

名字结尾字母只有 26 种，读入时按结尾字母分 26 个桶，每个桶内按「评分降序、同分先读入在前」排好序，排序后桶内第 $k$ 个元素就是该字母下第 $k$ 大的名字。询问时桶内不足 $k$ 个就输出 `Orz YYR tql`，否则按下标直接取名字，单次询问 $O(1)$。

## 参考代码

@include-code(./main.cpp, cpp)