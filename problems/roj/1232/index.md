---
oj: "roj"
problem_id: "1232"
title: "Crossing River"
description: "排序后按最慢者递推：最快者往返快递一人，或两名最快者摆渡两名最慢者，逐个取较小值。"
difficulty: "普及-"
date: 2026-09-30 00:56
updated: 2026-10-05 06:04
toc: true
tags: ["贪心", "动态规划", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1232

---

[[TOC]]

## 题目描述

`t` 组数据，每组 `n` 个人要过河：船每次最多载 2 人，且至少 1 人把船划回，用时由船上较慢者决定，求把所有人送到对岸的最少总时间。输入第一行 `t`，之后每组第一行为 `n`、第二行为 `n` 个过河时间；输出每组一行答案。数据范围 $t \leqslant 10$，$n \leqslant 1000$，$a_i \leqslant 100$。样例：输入 `1 / 4 / 1 2 5 10`，输出 `17`。

## 思路

先排序，让当前最慢者永远是末尾；每轮只送走最慢者，要么最快者往返快递他一人（代价 $a_1+a_i$），要么两名最快者摆渡两名最慢者（代价 $a_1+2a_2+a_i$），两者取较小值逐层递推。

## 参考代码

@include-code(./main.cpp, cpp)
