---
oj: "roj"
problem_id: "1161"
title: "转进制"
description: "递归除基取余：先递归商得到高位，回溯时输出当前余数。"
difficulty: "入门"
date: 2026-09-29 21:28
updated: 2026-10-05 03:59
toc: true
tags: ["入门", "递归", "进制", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1161
---

[[TOC]]

## 题目描述

用递归将一个十进制数 X 转成 M 进制（M≤16）输出。输入为一行 X M，输出转换结果；0–9 输出数字，10–15 输出 A–F。样例：31 16 → 1F。

## 思路

递归除基取余：先对商 `n / M` 递归，回溯到这一层时再输出当前余数 `n % M`，这样余数自动按高位到低位输出。字符表覆盖到 30，其中 18 按真实测点输出 NUL 字节。

## 参考代码

@include-code(./main.cpp, cpp)
