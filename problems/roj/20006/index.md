---
oj: "roj"
problem_id: "20006"
title: "签到题:引号"
description: "用双引号把全文切成 n+1 段，再与无限交替的左、右 TeX 引号对拼接：第奇数个双引号换左引号、第偶数个换右引号。"
difficulty: "入门"
date: 2026-10-02 19:28
updated: 2026-10-06 02:18
toc: true
tags: ["入门", "字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20006
---

[[TOC]]

## 题目描述

输入一篇包含 ASCII 双引号 `"` 的文章，把它转换成 TeX 格式：第奇数个 `"` 换成左双引号 ``` `` ```，第偶数个 `"` 换成右双引号 `''`，其余字符原样输出。输入可能有多个行。

## 思路

全文顺序扫描，遇到 `"` 就按当前奇偶状态输出左/右引号并翻转状态，其它字符直接输出。单引号、反引号都不参与替换。

## 参考代码

@include-code(./main.cpp, cpp)
