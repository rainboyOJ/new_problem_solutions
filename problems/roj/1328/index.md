---
oj: "roj"
problem_id: "1328"
title: "【例7.7】光荣的梦想"
description: "最少相邻交换次数等于逆序对数，归并排序归并时统计跨段逆序对，O(n log n) 求解。"
difficulty: "普及-"
date: 2026-09-30 05:31
updated: 2026-10-07 12:15
toc: true
tags: ["逆序对", "归并排序", "分治", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1116"
    reason: "B 在证明「最少交换次数=逆序对数」时直接复用 A 教的那一步——交换相邻逆序对恰使逆序对数减 1（B 下界/上界都靠它），把问题化为数逆序对后再叠加 A 未教的归并排序跨段计数，得到 O(n log n)。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1328
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的数列，每次只能交换相邻两个元素，求把数列排成升序所需的最少交换次数。输入第一行 $n$，第二行 $n$ 个整数（$n \le 10000$）；输出最少交换次数。样例输入 `4 / 2 1 4 3`，样例输出 `2`。

## 思路

每次相邻交换最多消除一个逆序对，而数列无序时总能找到相邻逆序对进行交换，所以最少交换次数恰好等于逆序对数。用归并排序边归并边统计：右半元素出队时，左半剩余元素都比它大，累加左半剩余个数即可，复杂度 $O(n \log n)$。

## 参考代码

@include-code(./main.cpp, cpp)
