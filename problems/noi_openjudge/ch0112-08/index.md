---
oj: "noi_openjudge"
problem_id: "ch0112-08"
title: "Vigenère密码"
description: "按循环密钥反向平移密文字母，同时保留密文中的大小写。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/08/
---

[[TOC]]

### 题意

给定 Vigenere 密钥和密文，解密得到原明文；密钥忽略大小写，输出保持密文位置的大小写。

### 思路

将密钥字母转成 $0$ 到 $25$ 的位移量。第 `i` 个密文使用 `key[i % len(key)]`，解密就是字母编号减去位移后模 26。根据密文字母大小写选择对应的 ASCII 基准值。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

循环密钥可由下标对密钥长度取模实现，无需真的扩展字符串。
