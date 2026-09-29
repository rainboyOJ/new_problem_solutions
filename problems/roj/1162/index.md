---
oj: "roj"
problem_id: "1162"
title: "字符串逆序"
description: "读取以 '!' 结尾的字符串，定位终止符后把前面字符切片并反转输出。"
difficulty: "入门"
date: 2026-09-29 21:25
updated: 2026-09-29 21:25
toc: true
tags: ["字符串", "入门", "字符串反转"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1162
---

[[TOC]]

## 形式化题目

给定一个以字符 `'!'` 结尾的字符序列 $s_1 s_2 \dots s_k \texttt{!}$，要求输出 $s_k s_{k-1} \dots s_1$。

样例：
- 输入：`abc!`
- 输出：`cba`

## 正解

### 思路

把输入当作普通字符串读入，找到终止符 `'!'`，取它前面的子串，再用 Python 的切片语法 `[::-1]` 一次性反转输出。

由于字符串长度就是线性规模，读入、定位、反转三步都是 $O(n)$，没有更复杂的优化空间。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，$n$ 为 `'!'` 之前的字符数。
- 空间复杂度：$O(n)$，需要保存输入字符串和反转后的新字符串。

## 总结

本题是字符串基础操作。关键是把 `'!'` 当作结束标记，不参与输出；反转可以直接使用语言内置的切片完成。
