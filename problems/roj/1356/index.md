---
oj: "roj"
problem_id: "1356"
title: "计算(calc)"
description: "用调度场算法把中缀算式转成后缀表达式再求值，一次线性扫描即可处理括号与全部运算符"
difficulty: "普及-"
date: 2026-09-30 06:51
updated: 2026-10-06 07:45
toc: true
tags: ["字符串", "栈", "表达式求值"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1331"
    reason: "B 先用调度场算法把中缀转成后缀，再照搬 A 教的后缀求值「先弹右、后弹左」弹栈步骤；A 的入门题就是这条求值线的起点，B 只在其上叠加优先级与括号流程。"
  - oj: "leetcodecn"
    problem_id: "valid-parentheses"
    reason: "A 教的两类括号分别入栈/消解至配对左括号这一步，被 B 的调度场括号屏障规则直接复用，B 只是再叠加优先级弹栈与后缀求值"
common: []
recommend: []
source: https://roj.ac.cn/problem/1356
---

[[TOC]]

## 题目描述

给定一个中缀算式字符串，只包含括号 `(` `)`、数字 `0-9`、双目运算符 `+ - * / ^`，求算式的值。`/` 为整数除法（商向零截断），`^` 为乘方，括号保证配对且算式合法。

输入一行算式，输出一行整数结果。

样例：输入 `1+(3+2)*(7^2+6*9)/(2)`，输出 `258`。

## 思路

用调度场算法把中缀式转成后缀表达式：数字直接输出，遇到 `(` 入栈，`)` 则弹出到 `(` 为止，普通运算符先弹出栈里优先级不低于它的运算符再入栈。最后用另一个栈对后缀表达式求值，数字入栈，运算符弹出栈顶两个数计算后压回。

## 参考代码

@include-code(./main.cpp, cpp)
