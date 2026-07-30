---
oj: "noi_openjudge"
problem_id: "ch0113-03"
title: "八进制小数"
description: "将八进制小数看成以 8 的幂为分母的精确值，再用 Decimal 输出。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["进制转换", "高精度", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/03/
---

[[TOC]]

### 题意

将 $(0,1)$ 之间的有限八进制小数转换成等值的十进制有限小数，并按指定等式格式输出。

### 思路

小数点后的 $k$ 位八进制数去掉小数点后得到整数 $p$，原数就是 $p / 8^k$。分母只含因子 2，因此十进制表示一定有限。`Decimal` 配合足够精度可避免二进制浮点产生的尾差，最后去掉末尾零。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(k)$，空间复杂度为 $O(k)$。

### 总结

进制小数的位数对应分母的幂次，先写成分数最容易保证精确性。
