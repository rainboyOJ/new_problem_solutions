---
oj: "roj"
problem_id: "2001"
title: "usaco-1.1.2 贪婪的礼物送礼者"
description: "用 map 把名字映射为下标，按送礼顺序模拟：人均 m/cnt、余数自留，最后按读入顺序输出每人净额。"
difficulty: "入门"
date: 2026-10-01 02:15
updated: 2026-10-06 08:59
toc: true
tags: ["入门", "模拟", "字符串", "哈希表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2001
---

[[TOC]]

## 题目描述

$n$ 个人按输入顺序编号 $1\sim n$（$n\le 20$），每人初始钱数为 $0$。随后给出若干条送礼记录直到文件末尾：先给出送钱人名字，接着一行两个整数 $m$、$cnt$，表示送出 $m$ 元给 $cnt$ 个人；若 $cnt>0$，下面 $cnt$ 行每行一个接收者名字。每人分到 $\lfloor m/cnt\rfloor$ 元，余数 $m\bmod cnt$ 由送钱人自留；$cnt=0$ 时不发生任何转移。按读入顺序输出每个人最终钱数。

## 思路

把名字用 `map<string,int>` 映射成下标，维护一个钱数数组。逐条读取送礼记录：若 $cnt>0$ 则算出商和余数，送钱人扣掉实际分出的钱，每个接收者加上商；$cnt=0$ 则跳过。最后按名字输入顺序输出数组。

## 参考代码

@include-code(./main.cpp, cpp)
