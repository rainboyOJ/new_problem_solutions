---
oj: "roj"
problem_id: "3586"
title: "瑞士轮"
description: "每轮按当前排名两两配对、胜者加一分的瑞士轮模拟：发现胜者组与负者组各自保持有序，用归并代替每轮整体排序，复杂度从 O(RN log N) 降到 O(N log N + RN)。"
difficulty: "普及"
date: 2026-10-02 09:16
updated: 2026-10-06 14:34
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3586
---

[[TOC]]

## 题目描述

$2N$ 名编号 $1\sim 2N$ 的选手进行 $R$ 轮瑞士轮：每轮开始前按总分（初始分加已得分数，同分编号小者靠前）排名，第 $2k-1$ 名与第 $2k$ 名比赛，实力高者获胜并得 1 分；求 $R$ 轮结束后第 $Q$ 名的选手编号。

输入第一行 $N,R,Q$，第二行 $2N$ 个初始分数 $s_i$，第三行 $2N$ 个实力值 $w_i$；输出一个整数，即第 $Q$ 名选手的编号。数据范围 $1\le N\le10^5$，$1\le R\le50$，$1\le Q\le 2N$，$0\le s_i\le10^8$，$w_i$ 两两不同。样例输入三行 `2 4 2`、`7 6 6 7`、`10 5 20 15`，输出 `1`。

## 思路

朴素做法每轮整体排序是 $O(RN\log N)$。注意到每轮胜者分数同时加 1、负者分数不变，因此按赛前名次列出的胜者组和负者组各自仍有序，新一轮排名只需把这两个有序表归并一次，总复杂度降到 $O(N\log N+RN)$。

## 参考代码

@include-code(./main.cpp, cpp)
