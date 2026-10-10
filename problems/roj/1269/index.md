---
oj: "roj"
problem_id: "1269"
title: "【例9.13】庆功会"
description: "多重背包：把每种奖品的限购 s 二进制拆分成若干份捆绑，转成 0/1 背包求解最大总价值。"
difficulty: "普及"
date: 2026-09-30 02:37
updated: 2026-10-05 07:38
toc: true
tags: [动态规划, 背包, 多重背包, 二进制拆分, Python]
favorite: false
favorite_reason: ""
categories: [题解]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1269
---

[[TOC]]

## 题目描述

班级庆功会拨款买奖品，已知 $n$（$n \leqslant 500$）种奖品的单价 $v_i \leqslant 100$、单件价值 $w_i \leqslant 1000$、限购数量 $s_i \leqslant 10$，拨款总额 $m \leqslant 6000$，求能取得的最大总价值。

输入第一行为 $n\,m$；随后 $n$ 行每行 $v\;w\;s$。输出一个数：最大价值（注意是价值不是价格）。样例：输入 `5 1000 / 80 20 4 / 40 50 9 / 30 50 7 / 40 30 6 / 20 20 1`，输出 `1040`。

## 思路

多重背包的标准做法：把每种奖品的限购 $s$ 拆成 $1,2,4,\dots$ 及余数共约 $\log s$ 个捆绑份，每份看成一个 0/1 物品；对所有捆绑份跑一维 0/1 背包，预算 $j$ 从大到小更新保证只读旧值，时间 $O(nm\log s)$、空间 $O(m)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)