---
oj: "roj"
problem_id: "1055"
title: "判断闰年"
description: "按公历规则做一次布尔判断：被 4 整除且（非整百年或被 400 整除）即闰年，O(1) 输出 Y/N。"
difficulty: "入门"
date: 2026-09-29 16:34
updated: 2026-10-04 23:43
toc: true
tags: ["分支", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1055
---

[[TOC]]

## 题目描述

判断公元 $a$ 年（$0 < a < 3000$）是否为公历闰年：是则输出 `Y`，否则输出 `N`。输入只有一行一个整数 $a$，输出一行 `Y` 或 `N`。样例：输入 `2006`，输出 `N`。

## 思路

公历闰年规则是三层特例链：能被 4 整除是闰年，但整百年（被 100 整除）必须再被 400 整除才是闰年，即 $a \bmod 4 = 0 \land (a \bmod 100 \neq 0 \lor a \bmod 400 = 0)$，注意 1900 是平年、2000 是闰年。时间空间均为 $O(1)$。

## 参考代码

@include-code(./main.cpp, cpp)
