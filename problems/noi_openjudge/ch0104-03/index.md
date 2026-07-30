---
oj: "noi_openjudge"
problem_id: "ch0104-03"
title: "奇偶数判断"
description: "用 n%2 判断奇偶，并用条件表达式输出结果。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/03/
---

[[TOC]]

### 题意

判断正整数是奇数还是偶数。

### 思路

偶数除以 2 的余数为 0，奇数的余数非零。Python 中非零整数在条件位置视为真，因此 `"odd" if number % 2 else "even"` 可直接选择答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

只有两个短输出分支时，条件表达式比完整 `if` 更紧凑。
