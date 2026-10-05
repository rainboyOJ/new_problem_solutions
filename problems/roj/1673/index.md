---
oj: "roj"
problem_id: "1673"
title: "彩笔"
description: "边扫边用数组记下每种颜色首次出现的笔编号，第二次遇到同色即输出两个编号，扫完无重复则输出 different。"
difficulty: "入门"
date: 2026-10-01 01:37
updated: 2026-10-06 01:45
toc: true
tags: ["字符串", "哈希表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1673
---

[[TOC]]

## 题目描述

一个 16 格的彩笔盒，每格一支笔，颜色用大写字母表示。输入一行 16 个大写字母；题面保证若有同色，只会有一种且恰好 2 支。
若 16 支颜色全不同输出 `different`，否则按先小后大的顺序输出那两支同色笔的编号。样例输入 `ABCDEFAHIJPLMNOT`，样例输出 `1 7`。

## 思路

从左往右扫一遍，用数组记下每种颜色首次出现的编号；扫到已登记的颜色时，读出的旧编号一定更小，直接输出旧编号与当前编号。
扫完都没命中就输出 `different`。

## 参考代码

@include-code(./main.cpp, cpp)
