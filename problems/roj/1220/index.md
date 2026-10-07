---
oj: "roj"
problem_id: "1220"
title: "单词接龙"
description: "预处理每对单词的最小合法重叠增益，再按增益降序做带上界剪枝的 DFS 回溯，每词最多用两次，搜出最长接龙。"
difficulty: "普及"
date: 2026-09-30 00:22
updated: 2026-10-07 12:15
toc: true
tags: ["搜索", "DFS", "回溯", "剪枝", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1605"
    reason: "B 直接复用 A 教的「前进时标记、回溯时撤销」这一 DFS 回溯步骤，把 vis 布尔标记换成 used[word] 的次数计数（每词至多用两次），在此外层再叠加重叠增益预处理、增益降序枚举与 slack 上界剪枝。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1220
---

[[TOC]]

## 题目描述

单词接龙：给定 $n$ 个单词（$n\le 20$，只含大写或小写字母，长度不超过 20）和一个开头字母，用这些单词拼出一条最长的"龙"。每个单词最多出现两次；相邻两词相连时后缀与前缀的重合部分合并，且重合长度须严格小于两词长度（排除整词包含）。输入第一行一个整数 $n$，随后 $n$ 行各一个单词，最后一行为开头字母，输出以此字母开头的最长龙的长度。样例输入 `5 / at / touch / cheat / choose / tact / a`，样例输出 `23`。

## 思路

先预处理 `gain[i][j]`＝词 $j$ 接在词 $i$ 后的增益（词长减最小合法重叠，接不上记 0），一对词只保留最小重叠——重叠越短本次接出的龙越长，接完后后续只取决于结尾词；再按增益降序枚举后继做 DFS 回溯，每词最多用两次，并以 $slack=\sum_w(2-used_w)(|w|-1)$ 为剩余可增长量上界，满足 `当前长度 + slack <= ans` 时整枝剪掉。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
