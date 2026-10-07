---
oj: "roj"
problem_id: "3584"
title: "[NOIP2011-普及] 数字反转"
description: "先取绝对值，再逐位取末位拼成反转数；负号最后拼回，原数为 0 时结果为 0。"
difficulty: "普及-"
date: 2026-10-02 09:04
updated: 2026-10-07 13:50
toc: true
tags: ["输入输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0103-13"
    reason: "A 教的关键观察是把数字留在字符串域、用切片 [::-1] 倒序而不是拆位取模；B 的正解正是在这一步上叠加摘符号、lstrip('0') 去前导零与空串兜底，把范围从固定三位数扩到含负数与末尾零的任意整数。"
  - oj: "roj"
    problem_id: "20001"
    reason: "B 的字符串域解法直接复用 A 教的关键观察与表达式——反转后前导 0 就是原串末尾 0、用切片反转 + lstrip('0') 删净（另有空串兜底），只是在外面叠加了 abs 摘符号与 sign 拼回负号这一层。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3584
---

[[TOC]]

## 题目描述

给定一个整数 $N$，把它十进制数位反转得到一个新数。负号不参与反转，结果仍为负数时负号在最前面；除 $N=0$ 外，反转后的最高位不能是 $0$。数据范围 $|N|\le 10^9$。

## 思路

先取绝对值，然后不断取末位拼到结果后面，循环自然吃掉末尾零带来的前导零；最后再根据原数符号给结果加上负号。

## 参考代码

@include-code(./main.cpp, cpp)
