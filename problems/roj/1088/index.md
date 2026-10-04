---
oj: "roj"
problem_id: "1088"
title: "分离整数的各个数"
description: "反复用 n % 10 取出最低位，再用 n /= 10 去掉最低位，直到 n 为 0。"
difficulty: "入门"
date: 2026-09-29 18:17
updated: 2026-10-05 00:40
toc: true
tags: ["输入输出", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1088
---

[[TOC]]

## 题目描述

输入一个整数 $n$（$1 \le n \le 10^8$），从个位开始按从低位到高位的顺序输出它的每一位数字，数字之间用一个空格分隔。例如输入 `123`，输出 `3 2 1`。

## 思路

每轮用 `n % 10` 取出当前最低位，再用 `n /= 10` 把最低位删掉，循环直到 `n` 变为 0；这样得到的数字序列自然就是低位在前、高位在后。

## 参考代码

@include-code(./main.cpp, cpp)
