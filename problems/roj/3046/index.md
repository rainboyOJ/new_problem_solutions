---
oj: "roj"
problem_id: "3046"
title: "括号画家"
description: "用栈存未配对左括号的下标扫描一遍，失配的右括号成为断点，配对成功时用栈顶下标或断点算出以当前右括号结尾的最长合法子段。"
difficulty: "普及-"
date: 2026-10-01 11:53
updated: 2026-10-06 11:32
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3046
---

[[TOC]]

## 题目描述

达达画了一行由 `( )`、`[ ]`、`{ }` 组成的括号序列，长度 $N \leqslant 10^5$。美观（合法）序列定义为：空串美观；$A$ 美观则 `(A)`、`[A]`、`{A}` 美观；$A,B$ 都美观则 $AB$ 美观。求最长的美观连续子段长度。输入一行括号字符串，输出一个整数表示答案。样例输入 `({({(({()}})}{())})})[){{{([)()((()]]}])[{)]}{[}{)`，样例输出 `4`。

## 思路

用栈保存尚未配对的左括号下标，`barrier` 记最近一个失配右括号的下标。左括号入栈；右括号若与栈顶匹配就弹栈，此时以当前位置结尾的最长合法子段左端是新栈顶（栈空时为 `barrier`），用它更新答案；若失配则该右括号成为新 `barrier` 并清空栈（配对不能交叉）。每个下标至多进出栈一次，时间 $O(N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
