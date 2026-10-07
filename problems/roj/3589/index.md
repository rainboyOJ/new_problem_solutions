---
oj: "roj"
problem_id: "3589"
title: "[NOIP2011-提高] 选择客栈"
description: "固定右端点后，合法左端点只取决于它是否落在最近一家消费不超过 p 的客栈之前；一趟 O(n) 扫描按色调计数即可统计全部方案。"
difficulty: "普及"
date: 2026-10-02 09:16
updated: 2026-10-07 12:15
toc: true
tags: ["计数", "思维", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P9244"
    reason: "B 沿用 A 教的「固定右端点后按右端点归类计数」，把它从单变量 cnt 换成 valid/total 同色计数，只是把合法左端点的单调边界由 j-K+1 改为最近低价店 L(j)，并叠加 pending 摊还补记。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3589
---

[[TOC]]

## 题目描述

$n$ 家客栈排成一排，第 $i$ 家有色调 $c_i$（$0\sim k-1$）和咖啡店最低消费 $b_i$。统计有多少对 $i<j$ 满足：
1. 色调相同 $c_i=c_j$；
2. 区间 $[i,j]$ 内至少有一家咖啡店消费不超过 $p$。

**输入**：$n,k,p$，随后 $n$ 行每行 $c_i,b_i$。  
**输出**：合法方案总数。  
数据范围：$2\le n\le 200\,000$，$0\le k\le 10\,000$。

样例：$n=5,k=2,p=3$，客栈依次为 $(0,5),(1,3),(0,2),(1,4),(1,5)$，输出 $3$。

## 思路

固定右端点 $j$，设 $L(j)$ 为 $[1,j]$ 中最靠右的低价店位置。区间 $[i,j]$ 合法当且仅当 $i\le L(j)$。扫描时维护 `total[c]`（该色已出现次数）、`valid[c]`（位置 $\le L$ 的该色次数）和 `pending`（$L$ 右侧暂存的色调）。若 $b_j\le p$ 则 `ans += total[c]` 并清空 `pending` 补入 `valid`；否则 `ans += valid[c]` 并把 $c_j$ 加入 `pending$。一趟 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
