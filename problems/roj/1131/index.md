---
oj: "roj"
problem_id: "1131"
title: "基因相关性"
description: "逐位比较两条等长 DNA 序列统计相同碱基对个数，比例大于等于阈值即相关；一次线性扫描 O(n)。"
difficulty: "入门"
date: 2026-09-29 20:15
updated: 2026-10-05 02:53
toc: true
tags:
  - 字符串
  - 模拟
favorite: false
favorite_reason: ""
categories:
  - 字符串
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1131
---

[[TOC]]

## 题目描述

比对两条长度相同（长度不大于 $500$）的 DNA 序列：相同位置的碱基构成一个碱基对，两碱基相同则为相同碱基对；相同碱基对比例大于等于给定阈值时判定相关。输入第一行为阈值，随后两行各为一条 DNA 序列。输出一行，相关输出 `yes`，否则输出 `no`。样例输入 `0.85` / `ATCGCCGTAAGTAACGGTTTTAAATAGGCC` / `ATCGCCGGAAGTAACGGTCTTAAATAGGCC`，输出 `yes`。

## 思路

逐位比较两条序列，统计相同碱基对的个数 $k$。设序列长度为 $n$，判断 $k/n \geqslant x$ 是否成立即可，等于阈值也算相关。一遍线性扫描 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
