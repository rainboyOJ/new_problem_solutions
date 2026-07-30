---
oj: "noi_openjudge"
problem_id: "ch0107-29"
title: "ISBN号码"
description: "提取 ISBN 的九位数字计算加权和模 11，校验或替换识别码。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/29/
---

[[TOC]]

### 题意

校验 ISBN 最后一位识别码；错误时输出改正后的完整 ISBN。

### 思路

删除连字符后，前九个字符依次乘权重 $1$ 到 $9$ 并取模 $11$。余数 $10$ 用 `X` 表示。识别码错误时只替换原串最后一位，可保留三个连字符的位置。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

ISBN 长度固定，时间和额外空间复杂度均为 $O(1)$。

### 总结

格式串校验时，保留原格式并单独提取参与计算的字符最稳妥。
