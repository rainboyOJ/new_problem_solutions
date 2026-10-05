---
oj: "roj"
problem_id: "1406"
title: "单词替换"
description: "按空格把字符串拆成单词，逐词判断是否与目标单词完全相同并替换，最后用空格拼接输出。"
difficulty: "入门"
date: 2026-09-30 09:00
updated: 2026-10-05 23:02
toc: true
tags:
  - "string"
  - "simulation"
favorite: false
favorite_reason: ""
categories:
  - "字符串"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1406
---

[[TOC]]

## 题目描述

给定一行由单个空格分隔的单词组成的字符串 $s$（长度 $\le 200$），以及待替换单词 $a$、替换单词 $b$（长度均 $\le 100$），单词区分大小写。输入三行依次为 $s$、$a$、$b$，要求把 $s$ 中所有与 $a$ 完全相同的独立单词替换成 $b$，其余单词不变，输出替换后的字符串。样例输入为 `You want someone to help you`、`You`、`I` 三行，样例输出为 `I want someone to help you`。

## 思路

题目只替换独立单词，直接在原串上做子串替换会误伤包含 $a$ 的长单词（例如 $a=\text{"in"}$ 时误改 `inside`）。按空格把 $s$ 拆成单词，逐词与 $a$ 比较，相同则输出 $b$，否则原样输出，词间用一个空格分隔。

## 参考代码

@include-code(./main.cpp, cpp)
