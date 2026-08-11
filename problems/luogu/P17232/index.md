---
oj: "luogu"
problem_id: "P17232"
title: "[Algo Beat Contest 017 A] 串哈希"
description: "按 kirai、daishuki、shuki 的优先级检查子串并顺序模拟气压变化。"
difficulty: "入门"
date: 2026-08-11 07:37
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P17232
---

[[TOC]]

## 形式化题目

给定一个初始整数和一个字符串序列。依次处理每个字符串时，根据它是否包含若干固定子串，按指定优先级改变当前整数。全部处理后，根据最终整数是否为正输出数值差或固定字符串。

## 思路

这题的核心是“规则优先级”，不是哈希。每个字符串只需要判断是否包含三个固定子串：`kirai`、`daishuki`、`shuki`。

判断顺序必须和题面优先级一致：

1. 先判断 `kirai`。一旦出现，就忽略另外两条加分规则。
2. 再判断 `daishuki`。因为 `daishuki` 自身包含 `shuki`，所以它必须排在 `shuki` 前面。
3. 最后判断 `shuki`。
4. 都不包含时，气压减一。

遇到 `kirai` 时还要注意当前气压的符号：若当前气压非负，就把它设为 `0`；若已经为负，则保持不变。

处理完所有字符串后，设最终气压为 $t$。若 $t>0$，输出 $t-s$；否则输出 `shuki`。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设所有字符串长度总和为 $L$。每个字符串做常数次固定模式串查找，时间复杂度为 $O(L)$。

除读入字符串外，只维护当前气压，空间复杂度为 $O(1)$。

## 总结

这题容易错在 `daishuki` 包含 `shuki`，以及 `kirai` 的优先级最高。只要严格按题面顺序模拟，每一步气压变化就和定义一致。
