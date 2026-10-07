---
oj: "roj"
problem_id: "1139"
title: "整理药名"
description: "逐个药名逐字符规范化：首字符用 toupper 转大写，其余字符用 tolower 转小写，数字和 - 自动原样保留。"
difficulty: "入门"
date: 2026-09-29 20:37
updated: 2026-10-05 03:07
toc: true
tags: ["入门", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1139
---

[[TOC]]

## 题目描述

医生书写的药品名大小写混乱，需要整理成规范格式：第一个字符若是字母则大写，其余位置的字母一律小写，数字和 `-` 原样保留。

输入第一行一个整数 $n$（$n \le 100$），接下来 $n$ 行每行一个药品名，长度不超过 20，只由字母、数字和 `-` 组成。输出 $n$ 行，每行是对应的规范写法。

样例输入：

```
4
AspiRin
cisapride
2-PENICILLIN
Cefradine-6
```

样例输出：

```
Aspirin
Cisapride
2-penicillin
Cefradine-6
```

## 思路

每个药品名互相独立，逐个处理即可。对当前单词逐字符扫描：首字符用 `toupper` 转大写，其余字符用 `tolower` 转小写，而 `toupper`/`tolower` 对非字母字符返回原字符，`2-PENICILLIN` 这类带数字和 `-` 的名字就自动保留原样。总长度不超过 $100 \times 20 = 2000$，$O(\sum L_i)$ 的扫描完全够用。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
