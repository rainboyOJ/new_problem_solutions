---
oj: "noi_openjudge"
problem_id: "ch0108-25"
title: "螺旋加密"
description: "将字符转为五位二进制流，按顺时针螺旋写入矩阵后按行输出密文。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-06 07:45
toc: true
tags: ["矩阵", "字符串", "模拟", "编码", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "luogu"
    problem_id: "P5731"
    reason: "B 沿用 A 的顺时针螺旋顺序逐格填矩阵这一骨架（实现换成四边界收缩），把填数字换成填五位二进制密文"
  - oj: "noi_openjudge"
    problem_id: "ch0108-23"
    reason: "B 的螺旋填入复用 A 的四边界螺旋遍历这一步（走上、右、下、左边再整体收缩四条边界、单行单列跳过重复边），再叠加 A 未教的字符五位二进制编码、不足容量补零与按行拼接输出。"
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/25/
---

[[TOC]]

### 题意

把空格和大写字母编码为五位二进制数，按顺时针螺旋填入矩阵，最后按行输出二进制密文。

### 思路

空格映射为 $0$，字母映射为 $1$ 到 $26$，`f"{value:05b}"` 生成五位二进制。将不足矩阵容量的位补零后，用四边界螺旋路径写入，最后按行拼接。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设矩阵容量为 $RC$，时间和空间复杂度均为 $O(RC)$。

### 总结

螺旋加密由“字符到位流”和“位流到矩阵路径”两个独立步骤组成。
