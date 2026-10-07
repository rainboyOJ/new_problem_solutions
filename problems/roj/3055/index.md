---
oj: "roj"
problem_id: "3055"
title: "「Phone List」 电话列表"
description: "用 Trie 存所有号码并在末尾补哨兵，插入途中发现更早号码提前终止或当前号码结尾仍有后继即输出 NO。"
difficulty: "普及"
date: 2026-10-01 12:28
updated: 2026-10-06 11:42
toc: true
tags:
  - Trie
  - 字符串
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3055
---

[[TOC]]

## 题目描述

给定 $t$ 组数据，每组给出 $n$ 个仅由数字组成的电话号码（每个不超过 10 位）；若存在某个号码是另一个号码的前缀，列表不兼容，输出 `NO`，否则输出 `YES`。输入：第一行整数 $t$，每组数据第一行整数 $n$，接下来 $n$ 行每行一个号码。范围：$1 \le t \le 40$，$1 \le n \le 10000$。样例一：输入 `911`、`97625999`、`91125426`，输出 `NO`（`911` 是 `91125426` 的前缀）；样例二：输入 `113`、`12340`、`123440`、`12345`、`98346`，输出 `YES`。

## 思路

把每个号码逐字符插入 Trie，并在末尾额外走一个哨兵字符（数字里不存在的编号），让“某号码在此终止”也变成一条边；插入途中若发现下一个节点已挂着哨兵（更早的号码在此终止），或走到末尾时节点仍有后继（更早的号码从这里延伸下去），就说明存在前缀关系，输出 `NO`。每个字符只处理一次，单组复杂度为号码总长 $O(L)$，与插入顺序无关，一趟插入即可判定。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
