---
oj: "roj"
problem_id: "10006"
title: "涨薪"
description: "让工资最小的 k=n-x-y 人前两年连续拿 C 被开除，幸存 x+y 人年年涨薪：前 x 大乘 3^m、接下来 y 大乘 2^m，取模输出。"
difficulty: "普及"
date: 2026-10-02 17:43
updated: 2026-10-06 02:35
toc: true
tags: ["贪心", "排序", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P2676"
    reason: "B 复用 A 教的“先降序排序、再从最大元素开始取”的贪心：涨薪名额给工资最高的人最划算，故工资降序后取前 x 大之和，只是再叠加“开除最小的 n-x-y 人”与快速幂"
  - oj: "roj"
    problem_id: "1326"
    reason: "B 的 main.cpp 里 ll power(ll base,ll exp)（exp&1 时 result 乘底数、底数自身平方取模、exp>>=1）正是 A 教的「二进制分解快速幂：底数逐位平方升级、位为 1 时把底数乘进答案」这一步，用来算 $3^m$、$2^m$（m 可达 1e9），B 只是在此外层叠加降序排序与「最小 k=n-x-y 人连续两年拿 C 被开除」的贪心结论与 m=1 特判。"
  - oj: "roj"
    problem_id: "1616"
    reason: "B 的 main.cpp 中 ll power(ll base,ll exp)（result=result*base%MOD、base=base*base%MOD、exp>>=1）与 power(3,m)、power(2,m) 正是复用 A 教的「底数逐位平方、每一步取模」这一模快速幂步骤，用来把 m 年倍数 3^m、2^m 算成模值后代入 3^m S_x+2^m(S_{x+y}-S_x)；B 的 m 可达 1e9 使该步与 A 同样必要（main.py 用 pow(3,m,MOD)），另在其外叠加降序排序、前 k 大求和与剔除 k=n-x-y 人的贪心结论。"
common: []
recommend: []
source: https://roj.ac.cn/problem/10006
---

[[TOC]]

## 题目描述

公司有 $n$ 人，第 $i$ 人初始工资 $a_i$。每年选 $x$ 人绩效 A（工资 $\times 3$）、$y$ 人绩效 B（$\times 2$），其余绩效 C（工资不变），**连续两年绩效 C 会被开除**，且不招新人。输入第一行 $n,m,x,y$，第二行 $n$ 个 $a_i$；求 $m$ 年后在职员工工资总和的最大值，对 $10^9+7$ 取模。$1\leqslant n\leqslant 10^5$，$1\leqslant m\leqslant 10^9$，$1\leqslant a_i\leqslant 10^5$。

样例：`2 1 1 1` / `5 3` 输出 `21`；`2 2 0 0` / `5 2` 输出 `0`。

## 思路

工资降序排序后，$m\geqslant 2$ 时让最小的 $k=n-x-y$ 人前两年连续拿 C 被开除，此后在职者恰剩 $x+y$ 人年年涨薪、涨薪名额零浪费，故答案是 $3^m S_x+2^m(S_{x+y}-S_x)$，其中 $S_j$ 为前 $j$ 大工资之和。$m=1$ 时无人会被开除，拿 C 的人照领原工资，需再加 $S_n-S_{x+y}$。

## 参考代码

@include-code(./main.cpp, cpp)
