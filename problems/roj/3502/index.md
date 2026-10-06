---
oj: "roj"
problem_id: "3502"
title: "单词接龙"
description: "单词接龙求最长拼接：预处理每对词的最小合法重叠，再以“最后词 + 各词用量”为状态记忆化搜索最大长度。"
difficulty: "普及"
date: 2026-10-02 04:27
updated: 2026-10-06 12:09
toc: true
tags: ["搜索", "记忆化", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3502
---

[[TOC]]

## 题目描述

$n$（$n\le 20$）个单词接龙，首词须以给定字母开头，相邻两词须有重叠且只计一次（`beast`+`astonish`→`beastonish`），不能整词包含（`at` 不能接 `atide`），每词最多用两次，求最长龙的长度。

输入第一行 $n$，随后 $n$ 行单词，最后一行为首字母。样例：`5, at, touch, cheat, choose, tact, a` → 输出 `23`。

## 思路

后续能接多长只取决于最后一个词和各词已用次数，与前面路径无关。先预处理每对单词的最小合法重叠（$k<\min(|a|,|b|)$ 自动排除整词包含），再以「最后词 + 各词用量」为状态记忆化搜索，枚举接得上且未用满两次的后继取最大。

## 参考代码

@include-code(./main.cpp, cpp)
