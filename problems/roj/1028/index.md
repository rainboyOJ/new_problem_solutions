---
oj: "roj"
problem_id: "1028"
title: "字符菱形"
description: "按行距 g=|r-2| 生成 5 行字符菱形：前导空格数等于 g，字符数等于 5-2g。"
difficulty: "入门"
date: 2026-09-29 14:04
updated: 2026-10-04 22:50
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1028
---

[[TOC]]

## 题目描述

输入一个字符 $c$，输出由它组成的 5 行菱形。第 $r$ 行（$r=0\sim4$）为若干前导空格加连续 $c$，行尾不留空格。样例 $c=\texttt{*}$：

```
  *
 ***
*****
 ***
  *
```

## 思路

第 $r$ 行到中间行的距离 $g=|r-2|$ 同时决定前导空格数与字符数：空格数 $=g$，字符数 $=5-2g$。逐行输出即可，注意不要用居中对齐补右侧空格。

## 参考代码

@include-code(./main.cpp, cpp)
