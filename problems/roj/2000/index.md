---
oj: "roj"
problem_id: "2000"
title: "毛毛的接送服务"
description: "将名字中的字母映射为 1 到 26 的数值并累乘模 47，判断两个名字所得模数是否相等。"
difficulty: "入门"
date: 2026-10-01 02:03
updated: 2026-10-06 02:04
toc: true
tags:
  - 模拟
  - 字符串
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2000
---

[[TOC]]

## 题目描述

每个人都有两个名字。名字中每个大写字母对应 1~26 的数值（A=1，Z=26），名字的最终数字是所有字母对应数值的乘积 mod 47。若两个名字的数值相等则输出 `GO`，否则输出 `STAY`。名字长度 1~6。

## 思路

遍历每个字符，将其转为对应数值后累乘并对 47 取模，分别计算两个名字的结果再比较即可。

## 参考代码

@include-code(./main.cpp, cpp)
