---
oj: "roj"
problem_id: "1140"
title: "验证子串"
description: "先判 s1 是否为 s2 的连续子串，再判 s2 是否为 s1 的子串，按题面固定的先后顺序输出三个分支。"
difficulty: "入门"
date: 2026-09-29 20:38
updated: 2026-10-05 03:21
toc: true
tags: ["入门", "字符串", "子串匹配", "python"]
favorite: false
favorite_reason: ""
categories:
  - 字符串
common:
  - oj: "noi_openjudge"
    problem_id: "ch0107-18"
    reason: "同一本通题目在 NOI OpenJudge 的对应版，输入输出与判定完全一致。"
showAtRbook: []
pre: []
recommend: []
source: https://roj.ac.cn/problem/1140
---

[[TOC]]

## 题目描述

输入两个不含空格的字符串 $s_1, s_2$（每行一个，长度不超过 200）。若 $s_1$ 是 $s_2$ 的连续子串，输出 `s1 is substring of s2`；否则，若 $s_2$ 是 $s_1$ 的子串，输出 `s2 is substring of s1`；否则输出 `No substring`。如输入 `abc`、`dddncabca`，则输出 `abc is substring of dddncabca`。

## 思路

枚举 $s_2$ 的每个起点 $k$，比较长度为 $|s_1|$ 的窗口 $s_2[k:k+|s_1|]$ 是否整段等于 $s_1$。分支必须先判 $s_1 \sqsubseteq s_2$、后判 $s_2 \sqsubseteq s_1$，两串全等时才能输出方向一。长度不超过 200，朴素 $O(|s_1| \cdot |s_2|)$ 足够。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
