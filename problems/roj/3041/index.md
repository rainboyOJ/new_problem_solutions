---
oj: "roj"
problem_id: "3041"
title: "前缀统计"
description: "把 N 个模式串建成 Trie 并在每个结点记录结尾计数，每个询问沿路径走一遍累加经过结点的计数，O(总长度) 建树、每次询问 O(|T|) 回答。"
difficulty: "普及"
date: 2026-10-01 11:39
updated: 2026-10-06 11:32
toc: true
tags: ["Trie", "字典树", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3041
---

[[TOC]]

## 题目描述

给定 $N$ 个模式串和 $M$ 次询问，每次给一个字符串 $T$，求 $S_1 \sim S_N$ 中有多少串是 $T$ 的前缀。字符串仅含小写字母，输入总长度不超过 $10^6$。

## 思路

把所有模式串插入 Trie，每个结点记录在此结尾的串数；询问时沿 $T$ 从根往下走，把路径上各结点的结尾计数累加即为答案。询问中某条边不存在时可直接停止。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
