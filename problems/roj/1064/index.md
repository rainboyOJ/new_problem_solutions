---
oj: "roj"
problem_id: "1064"
title: "奥运奖牌计数"
description: "读入每天的金、银、铜牌数，分别累加后输出三列之和与总奖牌数。"
difficulty: "入门"
date: 2026-09-29 16:58
updated: 2026-10-04 23:57
toc: true
tags: ["入门", "模拟", "数组"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1064
---

[[TOC]]
## 题目描述
输入第1行为天数n（1≤n≤17），其后n行每行3个整数为当天金、银、铜牌数；输出金、银、铜牌总数及总奖牌数。
输入样例：
```
3
1 0 3
3 1 0
0 3 0
```
输出样例：`4 4 3 11`
## 思路
用三个计数器分别累加三列奖牌数，最后求和得到总奖牌数。
## 参考代码
@include-code(./main.cpp, cpp)
