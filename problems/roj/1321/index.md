---
oj: "roj"
problem_id: "1321"
title: "【例6.3】删数问题(Noip1994)"
description: "删除顺序等价于每次删第一个下降位；用单调不减栈一次扫描，弹出次数正好等于删除名额，剩余名额删末尾，时间 O(L)。"
difficulty: "普及"
date: 2026-09-30 05:05
updated: 2026-10-05 09:41
toc: true
tags: ["字符串", "贪心", "单调栈", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common:
  - oj: "luogu"
    problem_id: "P1106"
    reason: "同一题模型：同样是删 k 位使剩余数字最小，单调栈 + 去前导零，可直接互相对照。"
recommend: []
source: https://roj.ac.cn/problem/1321
---

[[TOC]]

## 题目描述

输入一个高精度正整数 $n$（不超过 240 位，首位不为 0），去掉其中任意 $s$（$s < $ 位数）个数字后，剩下的数字按原左右次序组成一个新的正整数。编程寻找一种方案使新数最小，输出这个最小数。输入数据均不需判错。

输入两行：第一行为 $n$，第二行为 $s$。

输出最后剩下的最小数（若剩下的数字全是 0，输出 `0`）。

```input
175438
4
```

```output
13
```

## 思路

剩下的位数固定为 $L-s$，比较数值就是比较字典序；贪心规则是：从左往右遇到第一个下降位 $a_i > a_{i+1}$ 就删掉 $a_i$，串已单调不减时删末位。用一个单调不减栈一次扫描实现：读入新数字时只要栈顶比它大且还有删除名额就弹出栈顶，扫描结束后名额没用完就从栈尾继续删，最后剥掉前导零输出，总时间 $O(L)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
