---
oj: "roj"
problem_id: "1135"
title: "配对碱基链"
description: "按 A↔T、G↔C 的配对规则逐位替换，一遍扫描输出互补链。"
difficulty: "入门"
date: 2026-09-29 20:26
updated: 2026-10-05 02:58
toc: true
tags: ["入门", "字符串", "映射", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1135
---

[[TOC]]

## 题目描述

DNA 的两条互补链在对应位置上按 A 与 T 配对、G 与 C 配对。给定一条只含 `A`、`T`、`G`、`C` 的碱基链（长度不超过 255），求它的互补链。输入一行表示一条碱基链，输出一行表示与它互补的碱基链。样例输入 `ATATGGATGGTGTTTGGCTCTG`，输出 `TATACCTACCACAAACCGAGAC`。

## 思路

每个位置的互补碱基只由该位置自己的碱基决定，与相邻位置无关：`A` 换成 `T`、`T` 换成 `A`、`G` 换成 `C`、`C` 换成 `G`。从左到右逐位替换输出即可，时间复杂度 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
