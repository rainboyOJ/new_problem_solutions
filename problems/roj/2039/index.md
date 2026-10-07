---
oj: "roj"
problem_id: "2039"
title: "分数化小数"
description: "模拟竖式长除法，用字典登记余数第一次出现的位置：余数重复即找到循环节，余数变 0 即有限小数，总步数不超过分母。"
difficulty: "普及-"
date: 2026-10-01 04:30
updated: 2026-10-06 02:35
toc: true
tags: ["模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1082"
    reason: "B 的循环体直接复用 A 教的长除法取位步骤（余数乘 10 取商、余数取模），只是额外登记余数首次出现的位数以定位循环节"
common: []
recommend: []
source: https://roj.ac.cn/problem/2039
---

[[TOC]]
## 题目描述
输入一个分数 $N/D$（$1 \leqslant N, D \leqslant 100000$），输出它的小数形式：循环节用一对圆括号括起来（如 $1/3$ 写成 `0.(3)`），整数写成 `xxx.0`。输出串长度超过 76 个字符时，每 76 个字符换一行。
样例输入：`45 56`；样例输出：`0.803(571428)`。
## 思路
模拟竖式长除法：每一步的商位由当前余数唯一决定，用数组登记每个余数第一次出现时已写出的小数位数。
余数变 0 就是有限小数（一位没写补 `0`）；某个余数第二次出现时，它第一次出现的位置之后就是循环节，加上括号即可。
余数只有 $D$ 种取值，$O(D)$ 步内必然终止。
## 参考代码
@include-code(./main.cpp, cpp)
