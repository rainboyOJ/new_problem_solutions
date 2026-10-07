---
oj: "roj"
problem_id: "2016"
title: "usaco-1.4.4 母亲的牛奶"
description: "把三个桶的牛奶量当作状态、完全灌注当作边，在至多 441 个节点的隐式有向图上做可达性遍历，收集 A 空时的 C 值并升序输出。"
difficulty: "普及-"
date: 2026-10-01 03:06
updated: 2026-10-06 09:33
toc: true
tags:
  - "搜索"
  - "图论"
  - "BFS"
  - "python"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2016
---

[[TOC]]

## 题目描述

农民约翰有三个容量分别为 $A,B,C$ 的桶（$1\leqslant A,B,C\leqslant20$）。初始 A、B 为空，C 装满。每次选两个不同的桶，把源桶的牛奶倒向目标桶，直到目标桶满或源桶空。求 A 桶为空时，C 桶牛奶剩余量的所有可能值，升序输出一行。

样例输入 `8 9 10` 输出 `1 2 8 9 10`；输入 `2 5 10` 输出 `5 6 7 8 9 10`。

## 思路

状态用三元组 $(a,b,c)$ 表示，总量守恒 $a+b+c=C$，所以不同状态不超过 $(A+1)(B+1)\leqslant441$ 个。一次合法倒出量为 $\Delta=\min(m_{src},\;c_{dst}-m_{dst})$。从 $(0,0,C)$ 出发，用栈做 DFS（或 BFS），`vis` 判重，每个状态只扩展一次，遍历完收集 $a=0$ 的所有 $c$ 升序输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
